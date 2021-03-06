/*
 * AP_VirtualWP.cpp
 *
 *  Created on: June 06, 2017
 *      Author: Alessandro Benini
 */

#include "AP_VirtualWP.h"

const AP_Param::GroupInfo VirtualWP::var_info[] = {

    // @Param: VWP_ENABLE
    // @DisplayName: Enabling virtual waypoint feature
    // @Description: This parameter allows to enable/disable the virtual waypoint feature. By default this feature is disabled.
    // @User: Standard
    // @Units: Boolean
    // @Range: 0 1
    // @Increment: 1
    AP_GROUPINFO("ENABLE", 1, VirtualWP, vwp_enabled, 0),

    // @Param: HEADING_WIND
    // @DisplayName: Heading with respect to the wind direction
    // @Description: Heading with respect to the wind direction
    // @User: Standard
    // @Units: Degrees
    // @Range: 0 180
    // @Increment: 1
    AP_GROUPINFO("HDG_WIND", 2, VirtualWP, heading_wind, 0.0f),

    // @Param: VWP SPEED
    // @DisplayName: Virtual Waypoint Speed
    // @Description: Ths parameter allows to set the airspeed of the UAV during the navigation through the virtual waypoints.
    // @User: Standard
    // @Units: m/s
    // @Range: 15 30
    // @Increment: 1
    AP_GROUPINFO("SPEED", 3, VirtualWP, vwp_spd, 20.0f),  
  
    // @Param: DIST_VWP1
    // @DisplayName: Distance of VWP1 from landing WP
    // @Description: Desc - Distance of VWP1 from landing WP
    // @User: Standard
    // @Units: m
    // @Range: 20 500
    // @Increment: 1
    AP_GROUPINFO("DIST_L_1", 4, VirtualWP, dist_vwpl_1, 50.0f),

    // @Param: DIST_INCR
    // @DisplayName: Distance of VWP2 from landing WP
    // @Description: Desc - Distance of VWP2 from landing VWP1
    // @User: Standard
    // @Units: m
    // @Range: 20 500
    // @Increment: 1
    AP_GROUPINFO("DIST_1_2", 5, VirtualWP, dist_vwp1_2, 50.0f),

    // @Param: DIST_INCR
    // @DisplayName: Distance of VWP2 from landing WP
    // @Description: Desc - Distance of VWP3 from landing VWP2
    // @User: Standard
    // @Units: m
    // @Range: 20 500
    // @Increment: 1
    AP_GROUPINFO("DIST_2_3", 6, VirtualWP, dist_vwp2_3, 50.0f),

    AP_GROUPEND

};


VirtualWP::VirtualWP(AP_Mission& mission, AP_AHRS_NavEKF &ahrs):
	vwp_status(VWP_NOT_GENERATED),
	vwp_error(VWP_NO_ERROR),
	_mission(mission),
	_ahrs(ahrs),
	vwp_cfg{2,4}
{}

void VirtualWP::init_VWP(void)
{
    num_cmd = _mission.num_commands();
    
    // I initialize all the indexes with default values
    idx_landing_wp = -1;
    idx_last_mission_wp = -1;
    idx_vwp = 0;

    // I calculate all the indexes
    calc_index_landing_waypoint();
    calc_index_last_mission_waypoint();
    calc_index_virtual_waypoints();
    
    vwp1 = {};
    vwp2 = {};
    vwp3 = {};
    reduce_speed = {};
    
}

void VirtualWP::calc_index_landing_waypoint(void)
{

    // Command item used for iterating through the mission
    AP_Mission::Mission_Command current_cmd;

    // Start iterating from the end of the mission
    for(int16_t i=num_cmd-1; i>=0; i--)
    {
	_mission.get_next_nav_cmd(i, current_cmd);

	if(current_cmd.id == MAV_CMD_NAV_LAND)
	{
	    idx_landing_wp = current_cmd.index;
	    break;
	}
    }

    // If I ended the for loop and the return value is -1, it means that the current mission has no
    // landing waypoints.
    if(idx_landing_wp < 0)
    {
	//GCS_SEND_MSG("Landing WP not found. VWP generation aborted.");
	vwp_error = VWP_LANDING_WP_NOT_FOUND;
    }
}

void VirtualWP::calc_index_last_mission_waypoint(void)
{

    // Command item used for iterating through the mission
    AP_Mission::Mission_Command current_cmd;

    // Start iterating from the end of the mission, looking for the n-th last DO_NAV waypoint.
    for(int16_t i=num_cmd-1; i>=0; i--)
    {
	_mission.get_next_nav_cmd(i, current_cmd);

	if(current_cmd.id == MAV_CMD_NAV_WAYPOINT)
	{
	    idx_last_mission_wp = current_cmd.index;
	    break;
	}
    }

    if(idx_last_mission_wp < 0)
    {
	//GCS_SEND_MSG("Last Mission WP not found. VWP generation aborted.");
	vwp_error = VWP_LAST_MISSION_WP_NOT_FOUND;
    }
}

void VirtualWP::calc_index_virtual_waypoints()
{

    // Command item used for iterating through the mission
    AP_Mission::Mission_Command current_cmd;

    int16_t n = vwp_cfg.dist_lwp_idx;

    // Current number of NAV commands found
    int16_t curr_num_nav_cmd_idx = 0;

    // Start iterating from the end of the mission, looking for the n-th last DO_NAV waypoint.
    for(int16_t i=num_cmd-1; i>=0; i--)
    {
	_mission.get_next_nav_cmd(i, current_cmd);

	if(current_cmd.id == MAV_CMD_NAV_WAYPOINT)
	    ++curr_num_nav_cmd_idx;

	// When I reach the n-th DO_NAV command, I get out the loop
	if(curr_num_nav_cmd_idx == (n+1))
	{
	    idx_vwp = current_cmd.index;
	    break;
	}
    }

    // If I ended the for loop and the return value is zero, it means that
    // the current mission has up to 2 mission waypoints. It's not common but
    // it can happen.
    if(idx_vwp == 0)
	vwp_error = VWP_INDEX_NOT_FOUND;
}

bool VirtualWP::is_change_speed_cmd_issued(const AP_Mission::Mission_Command& cmd)
{
    if(cmd.index > idx_last_mission_wp && cmd.index < idx_landing_wp && cmd.id == MAV_CMD_DO_CHANGE_SPEED)
	return true;

    return false;
}

// This function generates the virtual waypoints to attach at the end of mission, right before the landing waypoint
void VirtualWP::generate_virtual_waypoints(const AP_Mission::Mission_Command& cmd)
{

    // Check if the current cmd is where I should generate the virtual waypoints and there are no errors
    if(cmd.index == idx_vwp && vwp_error == VWP_NO_ERROR)
    {
	//GCS_SEND_MSG("Generating VWP: %d",cmd.index);

	// If I reached the point, I attach the virtual waypoint to the end of the mission,
	// just before the landing waypoint

	// Retrieve information about the wind --------------------------------------------
	// I assume that at this point of the mission I have a good estimation of wind
	// speed and direction
	Vector3f wind;
	
	// _ahrs.get_NavEKF2().getWind(0,wind);
	// Wingboys uses old version of Pixhawk firmware
	_ahrs.get_NavEKF().getWind(wind);
	float windX = wind.x;
	float windY = wind.y;
	float modWind = sqrt(wind.x*wind.x+wind.y*wind.y);
	// GCS_SEND_MSG("WIND_SPD:%5.2f",modWind);
	// -------------------------------------------------------------------------------

	// Retrieve the landing waypoint from the mission
	AP_Mission::Mission_Command wp;
	// The index of the mission starts from 0.
	_mission.get_next_nav_cmd(idx_landing_wp, wp);

	// Conversion of latitude and longitude from degrees to meters -------------------
	// (The reference WP for the conversion is the landing WP)
	// More information at: https://knowledge.safe.com/articles/725/calculating-accurate-length-in-meters-for-lat-long.html
	float lat = wp.content.location.lat*TO_DEG_FORMAT;
	float lng = wp.content.location.lng*TO_DEG_FORMAT;

	float mdlat = METERS_PER_DEG_LAT(lat);
	float mdlng = METERS_PER_DEG_LNG(lat);

	// GCS_SEND_MSG("LLr:%12.4f,%12.4f",lat,lng);
	// GCS_SEND_MSG("LLm:%12.4f,%12.4f",mdlat,mdlng);

	// Coordinates of the virtual waypoints
	Location loc_vwp1, loc_vwp2, loc_vwp3;
	Location land_wp = wp.content.location;

	// Retrieve the last mission waypoint from the mission
	AP_Mission::Mission_Command last_mwp;
	_mission.get_next_nav_cmd(idx_last_mission_wp, last_mwp);

	float last_mwp_lat = last_mwp.content.location.lat*TO_DEG_FORMAT;
	float last_mwp_lng = last_mwp.content.location.lng*TO_DEG_FORMAT;
	float last_mwp_alt = last_mwp.content.location.alt/100.0f;
	
	float land_wp_lat = land_wp.lat*TO_DEG_FORMAT;
	float land_wp_lng = land_wp.lng*TO_DEG_FORMAT;
	float land_wp_alt = land_wp.alt/100.0;
	
	// -------------------------------------------------------------------------------
	// The following check prevents to have more than 15 degrees of drop between the 
	// last mission waypoint and the landing waypoint. The purpose is to have low speed
	// after the transition and avoid the high pitch.
	
	// Minimum distance between the landing waypoint and the last mission waypoint
	
	// sin(max_slope_deg*DEG_TO_RAD) cannot be zero since it is set as a constant value for the moment
	// minimum distance is set as max_altitude_drop * cotg(max_slope_angle).
	// In this case, we have 20*cotg(7degrees) = 20*8.1443 = 162.886.
	// This value has to be divided by 3, since we have 3 virtual waypoints.
	// Therefore minimum_distance is 54.29 --> 55 meters.
	
	float min_distance_last_phase = 100.0f;
	
	if(dist_vwpl_1 < min_distance_last_phase)
	  dist_vwpl_1 = min_distance_last_phase;
	
	float min_distance_between_waypoints = 40.0f;
	
	if(dist_vwp1_2 < min_distance_between_waypoints)
	  dist_vwp1_2 = min_distance_between_waypoints;
	
	if(dist_vwp2_3 < min_distance_between_waypoints)
	  dist_vwp2_3 = min_distance_between_waypoints;
	
	// Now I check the landing waypoint altitude. If the difference is greater than 20 meters, I set it to 20.
	
	float max_altitude_difference = 20.0f;
	
	// Altitude difference is expressed in centimeters
	float altitude_difference = last_mwp.content.location.alt - wp.content.location.alt;
	
	if(altitude_difference > 2000.0)
	  wp.content.location.alt = last_mwp.content.location.alt - 2000.0;

	if(altitude_difference < -2000.0)
	  wp.content.location.alt = last_mwp.content.location.alt + 2000.0;	  
	
	// -------------------------------------------------------------------------------

	// GCS_SEND_MSG("LAST M_WP:%10.6f,%10.6f,%8.3f",last_mwp_lat,last_mwp_lng,last_mwp_alt);

	// Default distance of VWP when there is no wind
	// Direction of the Wind (rad)
	float thetaWind = 0.0f;
	float new_theta_vwp = 0.0f;

	float dist_vwpl_2 = dist_vwp1_2 + dist_vwpl_1;
	float dist_vwpl_3 = dist_vwp2_3 + dist_vwpl_2;

	// WindX is the component of the wind along North Axis. WindY is the component of the wind along East Axis.
	thetaWind = atan2(windY,windX);
	// New theta is the wind direction
	new_theta_vwp = thetaWind + heading_wind*DEG_TO_RAD;
	// GCS_SEND_MSG("WIND_DIR:%f",thetaWind*180.0f/3.1415f);


	// GCS_SEND_MSG("OLD L_WP:%10.6f,%10.6f,%8.3f",land_wp_lat,land_wp_lng,land_wp_alt);
	// GCS_SEND_MSG("VWPS_DIRd:%f",new_theta_vwp*180.0f/3.1415f);

	// --------------------------------------------------------------------------------
	// Difference of altitude between the landing waypoint and the last mission waypoint (in cm)
	float altitude_diff = wp.content.location.alt - last_mwp.content.location.alt;
	float step = 0.0f;

	// GCS_SEND_MSG("ALT DIFF, STEP:%f,%f",altitude_diff,step);

	// Making sure we are not dividing by zero
	if( (vwp_cfg.num_vwp-1) > 0)
	    step = altitude_diff / (vwp_cfg.num_vwp-1);

	// Sanity check: I make sure that the altitude of each virtual waypoint is within
	// the specified range -- THIS CHECK SHOULD NOT BE USED ANYMORE
	if(step < -MAX_STEP_CM)
	{
	    step = -MAX_STEP_CM;
	    // GCS_SEND_MSG("STEP ALTITUDE SET TO -MAX");
	}
	if(step > MAX_STEP_CM)
	{
	    step = MAX_STEP_CM;
	    // GCS_SEND_MSG("STEP ALTITUDE SET TO MAX");
	}
	// --------------------------------------------------------------------------------

	// Calculate the coordinates of the first virtual waypoint -----------------------
	loc_vwp1.lat = land_wp.lat + dist_vwpl_1*cos(new_theta_vwp) / mdlat * 10000000.0f;
	loc_vwp1.lng = land_wp.lng + dist_vwpl_1*sin(new_theta_vwp) / mdlng * 10000000.0f;
	// The altitude is the same as the altitude of the last waypoint mission
	loc_vwp1.alt = last_mwp.content.location.alt + 3*step;
	loc_vwp1.options = 1<<0;

	// Print and save info about vwp1
	float vwp1_lat = loc_vwp1.lat*TO_DEG_FORMAT;
	float vwp1_lng = loc_vwp1.lng*TO_DEG_FORMAT;
	float vwp1_alt = loc_vwp1.alt/100.0f;
	// GCS_SEND_MSG("VWP1:%10.6f,%10.6f,%8.3f",vwp1_lat,vwp1_lng,vwp1_alt);
	// -------------------------------------------------------------------------------

	// Calculate the coordinates of the second virtual waypoint ----------------------
	loc_vwp2.lat = land_wp.lat + dist_vwpl_2*cos(new_theta_vwp) / mdlat * 10000000.0f;
	loc_vwp2.lng = land_wp.lng + dist_vwpl_2*sin(new_theta_vwp) / mdlng * 10000000.0f;
	// The altitude is the same as the altitude of the last waypoint mission
	loc_vwp2.alt = last_mwp.content.location.alt + 2*step;
	loc_vwp2.options = 1<<0;

	// Print and save info about vwp2
	float vwp2_lat = loc_vwp2.lat*TO_DEG_FORMAT;
	float vwp2_lng = loc_vwp2.lng*TO_DEG_FORMAT;
	float vwp2_alt = loc_vwp2.alt/100.0f;
	// GCS_SEND_MSG("VWP2:%10.6f,%10.6f,%8.3f",vwp2_lat,vwp2_lng,vwp2_alt);

	AP_Mission::Change_Speed_Command vwp2_spd;
	vwp2_spd.speed_type = 0;
	// The target speed is set as 80% of the current speed
	// float current_speed = ahrs.getLastGNDSpeed();
	float reduced_speed = vwp_spd; //current_speed*80.0f/100.0f;
	
	if(reduced_speed < MINIMUM_SPEED_DURING_VWP)
	  reduced_speed = MINIMUM_SPEED_DURING_VWP;
	
	vwp2_spd.target_ms = reduced_speed;
	
	// -------------------------------------------------------------------------------

	// Calculate the coordinates of the third virtual waypoint -----------------------
	loc_vwp3.lat = land_wp.lat + dist_vwpl_3*cos(new_theta_vwp) / mdlat * 10000000.0f;
	loc_vwp3.lng = land_wp.lng + dist_vwpl_3*sin(new_theta_vwp) / mdlng * 10000000.0f;
	// The altitude is the same as the altitude of the last waypoint mission
	loc_vwp3.alt = last_mwp.content.location.alt + step;
	loc_vwp3.options = 1<<0;

	float vwp3_lat = loc_vwp3.lat*TO_DEG_FORMAT;
	float vwp3_lng = loc_vwp3.lng*TO_DEG_FORMAT;
	float vwp3_alt = loc_vwp3.alt/100.0f;
	// GCS_SEND_MSG("VWP3:%10.6f,%10.6f,%8.3f",vwp3_lat,vwp3_lng,vwp3_alt);
	// -------------------------------------------------------------------------------

	// The last virtual waypoint and the landinig waypoint should have the same altitude.

	// Update the mission
	// GCS_SEND_MSG("REWRITE_M");

	// Remove the old landing waypoint
	// GCS_SEND_MSG("OLD L_WP IDX:%d",wp.index);
	// GCS_SEND_MSG("Before truncate:%d",mission.num_commands());
	
	// GCS_SEND_MSG("After truncate:%d",mission.num_commands());

	// Adding the extra-commands (they will have the parameter p1 set to AUTOGENERATED_ITEM)

	// AP_Mission::Mission_Command vwp3 = {};
	// Copy all the properties of the last mission waypoint
	vwp3 = last_mwp;
	// Overwrite command id and waypoint coordinates
	vwp3.id = MAV_CMD_NAV_WAYPOINT;
	vwp3.content.location = loc_vwp3;
	// Add the new command to the mission
	

	// AP_Mission::Mission_Command vwp2 = {};
	vwp2 = last_mwp;
	vwp2.id = MAV_CMD_NAV_WAYPOINT;
	vwp2.content.location = loc_vwp2;
	

	// AP_Mission::Mission_Command reduce_speed = {};
	reduce_speed.id = MAV_CMD_DO_CHANGE_SPEED;
	reduce_speed.content.speed = vwp2_spd;
	

	// AP_Mission::Mission_Command vwp1 = {};
	vwp1 = last_mwp;
	vwp1.id = MAV_CMD_NAV_WAYPOINT;
	vwp1.content.location = loc_vwp1;
	    

	if(vwp_enabled)
	{
	    _mission.truncate(idx_landing_wp);
	    _mission.add_cmd(vwp3);
	    _mission.add_cmd(vwp2);
	    // _mission.add_cmd(reduce_speed);
	    _mission.add_cmd(vwp1);
	    // For the moment the UAV will still land at the original landing waypoint
	    _mission.add_cmd(wp);
	}

	vwp_status = VWP_GENERATED;

	update_num_commands();

    }

}

void VirtualWP::update_num_commands()
{
    // num_cmd is updated with the total number of commands after adding the virtual waypoints
    if(vwp_status > VWP_NOT_GENERATED)
	num_cmd = _mission.num_commands();
}

void VirtualWP::restore_mission()
{
    // If I generate the virtual waypoints, I can remove them and restore the mission to its original state.
    if(vwp_enabled && vwp_status == VWP_GENERATED)
    {
	// Here I restore the original version of the mission (in case it should be reloaded)
	// GCS_SEND_MSG("Restoring original mission");
	AP_Mission::Mission_Command wp;

	// GCS_SEND_MSG("Number of commands: %d",num_commands);
	// The variable wp will contain the landinig waypoint that I need to restore
	_mission.get_next_nav_cmd(num_cmd-1, wp);
	uint16_t landing_wp_index = wp.index;
	// GCS_SEND_MSG("Landing WP index: %d",landing_wp_index);

	// If the last command is the landing (safety check)
	if(wp.id==MAV_CMD_NAV_LAND)
	{
	    // I remove the mission items starting from the index of the original landing waypoint
	    // GCS_SEND_MSG("Truncate mission at index: %d",idx_landing_wp);
	    // GCS_SEND_MSG("Number of commands before truncate: %d",mission.num_commands());
	    _mission.truncate(idx_landing_wp);
	    // GCS_SEND_MSG("Number of commands after truncate: %d",mission.num_commands());
	    // GCS_SEND_MSG("Re-adding landing WP");
	    _mission.add_cmd(wp);
	    // GCS_SEND_MSG("Number of commands after re-adding landing WP: %d",mission.num_commands());
	}

	// Change the status
	vwp_status = VWP_REMOVED;
	
	update_num_commands();

    }
}

bool VirtualWP::is_current_cmd_vwp(const AP_Mission::Mission_Command& cmd)
{
    // The virtual waypoints are supposed to be added between the last mission waypoint and the landing waypoint
    if(cmd.index > idx_last_mission_wp && cmd.index < idx_landing_wp && cmd.id == MAV_CMD_NAV_WAYPOINT)
	return true;

    return false;
}

