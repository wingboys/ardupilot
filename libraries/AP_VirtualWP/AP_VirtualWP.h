/*
 * AP_VirtualWP.h
 *
 *  Created on: June 06, 2017
 *      Author: Alessandro Benini
 */

#ifndef AP_VIRTUALWP_H_
#define AP_VIRTUALWP_H_

#include <AP_Mission/AP_Mission.h>
#include <GCS_MAVLink/GCS_MAVLink.h>
#include <AP_AHRS/AP_AHRS.h>

// Macro for converting the latitude and longitude back to decimal representation
#define TO_DEG_FORMAT 1.0e-7f
// Macro for calculating how many meters for 1 degree of latitude, given the current latitude in degrees.
#define METERS_PER_DEG_LAT(lat) 111132.954-559.822*cos(2*lat*DEG_TO_RAD)+1.175*cos(4*lat*DEG_TO_RAD)
// Macro for calculating how many meters for 1 degree of longitude, given the current latitude in degrees.
#define METERS_PER_DEG_LNG(lat) 111132.954*cos(lat*DEG_TO_RAD);

// This the maximum variation of altitude between two consecutive virtual waypoints (value expressed in meters)
#define MAX_STEP 20.0f
#define MAX_STEP_CM MAX_STEP*100.0f

#define MINIMUM_SPEED_DURING_VWP 20.0f

// List of states concerning the generation of the virtual waypoints
typedef enum vwp_generation_states {
	VWP_NOT_GENERATED = 0,
	VWP_GENERATED,
	VWP_REMOVED
} vwp_status_t;

// List of the possible error during the generation of the virtual waypoints
typedef enum vwp_error_states {
	VWP_NO_ERROR = 0,
	VWP_LANDING_WP_NOT_FOUND,
	VWP_LAST_MISSION_WP_NOT_FOUND,
	VWP_INDEX_NOT_FOUND
} vwp_error_status_t;

class VirtualWP
{
public:

    // Constructor
    VirtualWP(AP_Mission &mission, AP_AHRS_NavEKF &ahrs);

    // Destructor
    ~VirtualWP() {}

    // Structure for holding parameters
    static const struct AP_Param::GroupInfo var_info[];

    // Initialize the indexes for calculating the virtual waypoints
    void init_VWP(void);

    /// calc_index_landing_waypoint - returns the index of the landing waypoint. The landing waypoint
    /// should always be the last item. But this function is implemented in order to contemplate
    /// the case where further actions are programmed after the landing and/or to make sure that
    /// a landing waypoint is set.
    void calc_index_landing_waypoint(void);

    /// calc_index_last_mission_waypoint - returns the index of the last mission waypoint.
    void calc_index_last_mission_waypoint(void);

    /// calc_index_virtual_waypoints - return the index of the nav cmd item after which the vwp will be generated (referred to as CMD_VWP)
    /// returns 0 if the mission is shorter than the distance between landing waypoint and CMD_VWP
    void calc_index_virtual_waypoints();

    bool is_change_speed_cmd_issued(const AP_Mission::Mission_Command& cmd);
    
    /// generate_virtual_waypoints - generates the virtual waypoints based on the current settings and the wind direction.
    void generate_virtual_waypoints(const AP_Mission::Mission_Command& cmd);
    
    /// update_num_commands - updates the variable containing the number of commands in the mission. This function is called after
    /// the addition and removal of the virtual waypoints.
    void update_num_commands();
    
    /// is_current_cmd_vwp - returns true if the currennt command is a generated command (virtual waypoint)
    bool is_current_cmd_vwp(const AP_Mission::Mission_Command& cmd);
    
    void restore_mission();
    
    // Get methods
    bool	is_vwp_enabled()		{ return vwp_enabled; }
    AP_Float 	get_heading_wind()		{ return heading_wind; }
    AP_Float 	get_vwp_spd()			{ return vwp_spd; }
    
    AP_Float	get_dist_vwpl_1()		{ return dist_vwpl_1; }
    AP_Float	get_dist_vwp1_2()		{ return dist_vwp1_2; }
    AP_Float	get_dist_vwp2_3()		{ return dist_vwp2_3; }

    int16_t 	get_idx_last_mission_wp()	{ return idx_last_mission_wp; }
    int16_t 	get_idx_landing_wp()		{ return idx_landing_wp; }
    int16_t 	get_idx_vwp()			{ return idx_vwp; }

    int16_t	get_num_commands()		{ return num_cmd; }
    
    // Set methods
    void 	set_dist_vwpl_1(AP_Float _val)	{ dist_vwpl_1 = _val; }
    void 	set_dist_vwp1_2(AP_Float _val)	{ dist_vwp1_2 = _val; }
    void 	set_dist_vwp2_3(AP_Float _val)	{ dist_vwp2_3 = _val; }  

    // Status variables
    vwp_status_t vwp_status;
    vwp_error_status_t vwp_error;

protected:

    AP_Int8  vwp_enabled;
    AP_Float heading_wind;
    AP_Float vwp_spd;
    
    AP_Float dist_vwpl_1;
    AP_Float dist_vwp1_2;
    AP_Float dist_vwp2_3;

private:

    typedef struct {
      // The following variable set the point in the mission where the virtual waypoints are generated.
      // The point in the mission is calculated as the number of nav_commands from the landing waypoint.
      int16_t dist_lwp_idx;
      // Number of virtual waypoints to be generated. For the moment it will be fixed at 3.
      int16_t num_vwp;
    } vwp_config_t;

    vwp_config_t vwp_cfg;

    // Index of the item after which calculate the virtual waypoints
    int16_t idx_vwp;

    // Index of the last mission waypoint
    int16_t idx_last_mission_wp;
    
    // Index of the original landing waypoint
    int16_t idx_landing_wp;

    // Number of commands contained in the mission
    int16_t num_cmd;

    AP_Mission&		_mission;
    AP_AHRS_NavEKF&	_ahrs;

};


#endif