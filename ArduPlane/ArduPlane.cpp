/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

/*
   Lead developer: Andrew Tridgell
 
   Authors:    Doug Weibel, Jose Julio, Jordi Munoz, Jason Short, Randy Mackay, Pat Hickey, John Arne Birkeland, Olivier Adler, Amilcar Lucas, Gregory Fletcher, Paul Riseborough, Brandon Jones, Jon Challinger
   Thanks to:  Chris Anderson, Michael Oborne, Paul Mather, Bill Premerlani, James Cohen, JB from rotorFX, Automatik, Fefenin, Peter Meister, Remzibi, Yury Smirnov, Sandro Benigno, Max Levine, Roberto Navoni, Lorenz Meier, Yury MonZon

   Please contribute your ideas! See http://dev.ardupilot.com for details

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Plane.h"

#define SCHED_TASK(func, _interval_ticks, _max_time_micros) {\
    .function = FUNCTOR_BIND(&plane, &Plane::func, void),\
    AP_SCHEDULER_NAME_INITIALIZER(func)\
    .interval_ticks = _interval_ticks,\
    .max_time_micros = _max_time_micros,\
}

int one_sec_cnt = 0;
int _flag_cnt = 0;
bool mission_rewrote = false;
bool mission_restored = false;

bool vwp_status_printed = false;

/*
  scheduler table - all regular tasks are listed here, along with how
  often they should be called (in 20ms units) and the maximum time
  they are expected to take (in microseconds)
 */
const AP_Scheduler::Task Plane::scheduler_tasks[] PROGMEM = {
    SCHED_TASK(read_radio,              1,    700),
    SCHED_TASK(check_short_failsafe,    1,   1000),
    SCHED_TASK(ahrs_update,             1,   6400),
    SCHED_TASK(update_speed_height,     1,   1600),
    SCHED_TASK(update_flight_mode,      1,   1400),
    SCHED_TASK(stabilize,               1,   3500),
    SCHED_TASK(set_servos,              1,   1600),
    SCHED_TASK(read_control_switch,     7,   1000),
    SCHED_TASK(gcs_retry_deferred,      1,   1000),
    SCHED_TASK(update_GPS_50Hz,         1,   2500),
    SCHED_TASK(update_GPS_10Hz,         5,   2500),
    SCHED_TASK(navigate,                5,   3000),
    SCHED_TASK(update_compass,          5,   1200),
    SCHED_TASK(read_airspeed,           5,   1200),
    SCHED_TASK(update_alt,              1,   3400),
    SCHED_TASK(adjust_altitude_target,  5,   1000),
    SCHED_TASK(obc_fs_check,            5,   1000),
    SCHED_TASK(gcs_update,              1,   1700),
    SCHED_TASK(gcs_data_stream_send,    1,   3000),
    SCHED_TASK(update_events,           1,   1500),
    SCHED_TASK(check_usb_mux,           5,    300),
    SCHED_TASK(read_battery,            5,   1000),
    SCHED_TASK(compass_accumulate,      1,   1500),
    SCHED_TASK(barometer_accumulate,    1,    900),
    SCHED_TASK(update_notify,           1,    300),
    SCHED_TASK(read_rangefinder,        1,    500),
    SCHED_TASK(compass_cal_update,      1,    100),
#if OPTFLOW == ENABLED
    SCHED_TASK(update_optical_flow,     1,    500),
#endif
    SCHED_TASK(one_second_loop,        50,   1000),
    SCHED_TASK(check_long_failsafe,    15,   1000),
    SCHED_TASK(read_receiver_rssi,      5,   1000),
    SCHED_TASK(airspeed_ratio_update,  50,   1000),
    SCHED_TASK(update_mount,            1,   1500),
    SCHED_TASK(log_perf_info,         500,   1000),
    SCHED_TASK(compass_save,         3000,   2500),
    SCHED_TASK(update_logging1,         5,   1700),
    SCHED_TASK(update_logging2,         5,   1700),
#if FRSKY_TELEM_ENABLED == ENABLED
    SCHED_TASK(frsky_telemetry_send,   10,    100),
#endif
    SCHED_TASK(terrain_update,          5,    500),
    SCHED_TASK(update_is_flying_5Hz,   10,    100),
    SCHED_TASK(dataflash_periodic,      1,    300),
};

void Plane::setup() 
{
    cliSerial = hal.console;

    // load the default values of variables listed in var_info[]
    AP_Param::setup_sketch_defaults();

    AP_Notify::flags.failsafe_battery = false;

    notify.init(false);

    rssi.init();

    init_ardupilot();   

    // initialise the main loop scheduler
    scheduler.init(&scheduler_tasks[0], ARRAY_SIZE(scheduler_tasks)); 
}

void Plane::loop()
{
    // wait for an INS sample
    ins.wait_for_sample();

    uint32_t timer = micros();

    delta_us_fast_loop  = timer - fast_loopTimer_us;
    G_Dt                = delta_us_fast_loop * 1.0e-6f;

    if (delta_us_fast_loop > G_Dt_max && fast_loopTimer_us != 0) {
        G_Dt_max = delta_us_fast_loop;
    }

    if (delta_us_fast_loop < G_Dt_min || G_Dt_min == 0) {
        G_Dt_min = delta_us_fast_loop;
    }
    fast_loopTimer_us   = timer;

    mainLoop_count++;

    // tell the scheduler one tick has passed
    scheduler.tick();

    // run all the tasks that are due to run. Note that we only
    // have to call this once per loop, as the tasks are scheduled
    // in multiples of the main loop tick. So if they don't run on
    // the first call to the scheduler they won't run on a later
    // call until scheduler.tick() is called again
    uint32_t remaining = (timer + 20000) - micros();
    if (remaining > 19500) {
        remaining = 19500;
    }
    scheduler.run(remaining);
}

// update AHRS system
void Plane::ahrs_update()
{
    hal.util->set_soft_armed(arming.is_armed() &&
                   hal.util->safety_switch_state() != AP_HAL::Util::SAFETY_DISARMED);

#if HIL_SUPPORT
    if (g.hil_mode == 1) {
        // update hil before AHRS update
        gcs_update();
    }
#endif

    ahrs.update();

    if (should_log(MASK_LOG_ATTITUDE_FAST)) {
        Log_Write_Attitude();
    }

    if (should_log(MASK_LOG_IMU)) {
        Log_Write_IMU();
#if HAL_CPU_CLASS >= HAL_CPU_CLASS_75
        DataFlash.Log_Write_IMUDT(ins);
#endif
    }

    // calculate a scaled roll limit based on current pitch
    roll_limit_cd = g.roll_limit_cd * cosf(ahrs.pitch);
    pitch_limit_min_cd = aparm.pitch_limit_min_cd * fabsf(cosf(ahrs.roll));

    // updated the summed gyro used for ground steering and
    // auto-takeoff. Dot product of DCM.c with gyro vector gives earth
    // frame yaw rate
    steer_state.locked_course_err += ahrs.get_yaw_rate_earth() * G_Dt;
    steer_state.locked_course_err = wrap_PI(steer_state.locked_course_err);
    
    // update inertial_nav for neitzke
    inertial_nav.update(G_Dt);
}

/*
  update 50Hz speed/height controller
 */
void Plane::update_speed_height(void)
{
    if (auto_throttle_mode) {
	    // Call TECS 50Hz update. Note that we call this regardless of
	    // throttle suppressed, as this needs to be running for
	    // takeoff detection
        SpdHgt_Controller->update_50hz(tecs_hgt_afe());
    }
}


/*
  update camera mount
 */
void Plane::update_mount(void)
{
#if MOUNT == ENABLED
    camera_mount.update();
#endif

#if CAMERA == ENABLED
    camera.trigger_pic_cleanup();
#endif
}

/*
  read and update compass
 */
void Plane::update_compass(void)
{
    if (g.compass_enabled && compass.read()) {
        ahrs.set_compass(&compass);
        compass.learn_offsets();
        if (should_log(MASK_LOG_COMPASS)) {
            DataFlash.Log_Write_Compass(compass);
        }
    } else {
        ahrs.set_compass(NULL);
    }
}

/*
  if the compass is enabled then try to accumulate a reading
 */
void Plane::compass_accumulate(void)
{
    if (g.compass_enabled) {
        compass.accumulate();
    }    
}

/*
  try to accumulate a baro reading
 */
void Plane::barometer_accumulate(void)
{
    barometer.accumulate();
}

/*
  do 10Hz logging
 */
void Plane::update_logging1(void)
{
    if (should_log(MASK_LOG_ATTITUDE_MED) && !should_log(MASK_LOG_ATTITUDE_FAST)) {
        Log_Write_Attitude();
    }

    if (should_log(MASK_LOG_ATTITUDE_MED) && !should_log(MASK_LOG_IMU))
        Log_Write_IMU();
}

/*
  do 10Hz logging - part2
 */
void Plane::update_logging2(void)
{
    if (should_log(MASK_LOG_CTUN))
        Log_Write_Control_Tuning();
    
    if (should_log(MASK_LOG_NTUN))
        Log_Write_Nav_Tuning();

    if (should_log(MASK_LOG_RC))
        Log_Write_RC();

#if HAL_CPU_CLASS >= HAL_CPU_CLASS_75
    if (should_log(MASK_LOG_IMU))
        DataFlash.Log_Write_Vibration(ins);
#endif
}


/*
  check for OBC failsafe check
 */
void Plane::obc_fs_check(void)
{
#if OBC_FAILSAFE == ENABLED
    // perform OBC failsafe checks
    obc.check(OBC_MODE(control_mode), failsafe.last_heartbeat_ms, geofence_breached(), failsafe.last_valid_rc_ms);
#endif
}


/*
  update aux servo mappings
 */
void Plane::update_aux(void)
{
    RC_Channel_aux::enable_aux_servos();
}

void Plane::one_second_loop()
{
  
  if(!vwp_status_printed)
  {
      if(g.vwp_enabled==0)
	gcs_send_text_fmt(PSTR("VWP disabled"));
      else
	gcs_send_text_fmt(PSTR("VWP enabled"));  
      vwp_status_printed = true;
  }

//     if(g.vwp_enabled)
//     {
// 	one_sec_cnt += 1;
// 
// 	// After 60 seconds from the startup, the virtual waypoints will be added
// 	if(one_sec_cnt > 60 && !mission_rewrote)
// 	{
// 	  gcs_send_text_fmt(PSTR("Calling Mission Rewrite function"));
// 	  one_time_rewrite();
// 	  mission_rewrote = true;
// 	}
// 
// 	// The following section is used for restoring the original mission
// 	if(one_sec_cnt > 120 && !mission_restored)
// 	{
// 	  gcs_send_text_fmt(PSTR("Calling Mission Restore function"));
// 	  one_time_restore();
// 	  mission_restored = true;
// 	}
// 	
//     }  
  
    if (should_log(MASK_LOG_CURRENT))
        Log_Write_Current();

    // send a heartbeat
    gcs_send_message(MSG_HEARTBEAT);

    // make it possible to change control channel ordering at runtime
    set_control_channels();

    // make it possible to change orientation at runtime
    ahrs.set_orientation();

    // sync MAVLink system ID
    mavlink_system.sysid = g.sysid_this_mav;

    update_aux();

    // update notify flags
    AP_Notify::flags.pre_arm_check = arming.pre_arm_checks(false);
    AP_Notify::flags.pre_arm_gps_check = true;
    AP_Notify::flags.armed = arming.is_armed() || arming.arming_required() == AP_Arming::NO;

    crash_detection_update();

#if AP_TERRAIN_AVAILABLE
    if (should_log(MASK_LOG_GPS)) {
        terrain.log_terrain_data(DataFlash);
    }
#endif
    // piggyback the status log entry on the MODE log entry flag
    if (should_log(MASK_LOG_MODE)) {
        Log_Write_Status();
    }

#if HAL_CPU_CLASS >= HAL_CPU_CLASS_75
    ins.set_raw_logging(should_log(MASK_LOG_IMU_RAW));
#endif
}

void Plane::one_time_rewrite()
{
    
    gcs_send_text_fmt(PSTR("APMF - Number of commands: %d"),mission.num_commands());
    
    AP_Mission::Mission_Command _lastMWP;    
    AP_Mission::Mission_Command _landWP;
    
    gcs_send_text_fmt(PSTR("Current nav index: %d"),mission.get_current_nav_index());
    
    // The landing waypoint should be the last command.
    uint16_t _landWP_idx = mission.num_commands() - 1;
    uint16_t _lastMWP_idx = mission.num_commands() - 2;
    
    gcs_send_text_fmt(PSTR("LWP IDX: %d"),mission.get_current_nav_index());  
    
    mission.get_next_nav_cmd(_lastMWP_idx, _lastMWP); 
    mission.get_next_nav_cmd(_landWP_idx, _landWP);
    
    gcs_send_text_fmt(PSTR("LAST M_WP:%10.6f,%10.6f,%8.3f"),(double)_lastMWP.content.location.lat/10000000.0,(double)_lastMWP.content.location.lng/10000000.0,(double)_lastMWP.content.location.alt/100.0);

    // Conversion of latitude and logitude from degrees to meters (The reference WP for the conversion is the landing WP)
    // More information at: https://knowledge.safe.com/articles/725/calculating-accurate-length-in-meters-for-lat-long.html
    float latr = (_lastMWP.content.location.lat/10000000.0f)*3.1415/180.0;
    float lngr = (_lastMWP.content.location.lng/10000000.0f)*3.1415/180.0;

    float mdlat = 111132.954-559.822*cos(2*latr)+1.175*cos(4*latr);
    float mdlng = 111132.954*cos(latr);
    
    gcs_send_text_fmt(PSTR("LLr:%12.4f,%12.4f"),latr,lngr);
    gcs_send_text_fmt(PSTR("LLm:%12.4f,%12.4f"),mdlat,mdlng);

    // Coordinates of the virtual waypoints
    Location loc_vwp1, loc_vwp2, loc_vwp3;
    Location lwp = _landWP.content.location;
    
    // float heading_wind = g.heading_wind;
    float new_theta_vwp = g.heading_wind;
    float dist_vwp1 = g.dist_vwp1;
    float dist_incr = g.dist_incr;
    
    // Calculate the coordinates of the three virtual waypoints
    loc_vwp1.lat = lwp.lat + (dist_vwp1*cos(new_theta_vwp)) / mdlat * 10000000.0f;
    loc_vwp1.lng = lwp.lng + (dist_vwp1*sin(new_theta_vwp)) / mdlng * 10000000.0f;
    // The altitude is the same as the altitude of the last waypoint mission
    loc_vwp1.alt = _lastMWP.content.location.alt;
    loc_vwp1.options = 1<<0;
    
    Log_Write_VWP(99,loc_vwp1.lat/10000000.0f,loc_vwp1.lng/10000000.0f,loc_vwp1.alt/100.0f,1);
	    
    gcs_send_text_fmt(PSTR("VWP1:%10.6f,%10.6f,%8.3f"),(double)loc_vwp1.lat/10000000.0,(double)loc_vwp1.lng/10000000.0,(double)loc_vwp1.alt/100.0);

    loc_vwp2.lat = lwp.lat + ((dist_vwp1+dist_incr)*cos(new_theta_vwp)) / mdlat * 10000000.0f;
    loc_vwp2.lng = lwp.lng + ((dist_vwp1+dist_incr)*sin(new_theta_vwp)) / mdlng * 10000000.0f;
    // The altitude is the same as the altitude of the last waypoint mission
    loc_vwp2.alt = _lastMWP.content.location.alt;
    loc_vwp2.options = 1<<0;			
    gcs_send_text_fmt(PSTR("VWP2:%10.6f,%10.6f,%8.3f"),(double)loc_vwp2.lat/10000000.0,(double)loc_vwp2.lng/10000000.0,(double)loc_vwp2.alt/100.0);

    Log_Write_VWP(99,loc_vwp2.lat/10000000.0f,loc_vwp2.lng/10000000.0f,loc_vwp2.alt/100.0f,1);
	    
    loc_vwp3.lat = lwp.lat + ((dist_vwp1+2.0*dist_incr)*cos(new_theta_vwp)) / mdlat * 10000000.0f;
    loc_vwp3.lng = lwp.lng + ((dist_vwp1+2.0*dist_incr)*sin(new_theta_vwp)) / mdlng * 10000000.0f;
    // The altitude is the same as the altitude of the last waypoint mission
    loc_vwp3.alt = _lastMWP.content.location.alt;
    loc_vwp3.options = 1<<0;
    
    Log_Write_VWP(99,loc_vwp3.lat/10000000.0f,loc_vwp3.lng/10000000.0f,loc_vwp3.alt/100.0f,1);
	    
    gcs_send_text_fmt(PSTR("VWP3:%10.6f,%10.6f,%8.3f"),(double)loc_vwp3.lat/10000000.0,(double)loc_vwp3.lng/10000000.0,(double)loc_vwp3.alt/100.0);
    
    gcs_send_text_fmt(PSTR("[%d] - REWRITE MISSION"),_flag_cnt);
    
    // Remove the old landing waypoint
    gcs_send_text_fmt(PSTR("OLD L_WP IDX:%d"),_lastMWP.index);
    gcs_send_text_fmt(PSTR("Before truncate:%d"),mission.num_commands());
    mission.truncate(_landWP_idx);
    gcs_send_text_fmt(PSTR("After truncate:%d"),mission.num_commands());

    // Add the three virtual waypoints - The first VWP to be added is the farthest VWP

    AP_Mission::Mission_Command vwp3 = {};
    // Copy all the properties of the last mission waypoint
    vwp3 = _lastMWP;
    // Overwrite command id and waypoint coordinates
    vwp3.id = MAV_CMD_NAV_WAYPOINT;
    vwp3.content.location = loc_vwp3;
    // Add the new command to the mission
    mission.add_cmd(vwp3);

    AP_Mission::Mission_Command vwp2 = {};
    vwp2 = _lastMWP;
    vwp2.id = MAV_CMD_NAV_WAYPOINT;
    vwp2.content.location = loc_vwp2;
    mission.add_cmd(vwp2);

    AP_Mission::Mission_Command vwp1 = {};
    vwp1 = _lastMWP;
    vwp1.id = MAV_CMD_NAV_WAYPOINT;
    vwp1.content.location = loc_vwp1;
    mission.add_cmd(vwp1);

    // For the moment the UAV will still land at the original landing waypoint
    mission.add_cmd(_landWP);
    
    Log_Write_VWP(100,_landWP.content.location.lat/10000000.0f,_landWP.content.location.lng/10000000.0f,_landWP.content.location.alt/100.0,1);
    
    gcs_send_text_fmt(PSTR("Before Update:%d"),mission.num_commands());
    mission.update();
    gcs_send_text_fmt(PSTR("After Update:%d"),mission.num_commands());
    
    _flag_cnt += 1;
	
}

void Plane::one_time_restore()
{
  
    gcs_send_text_fmt(PSTR("OneTimeRestore-NumComm: %d"),mission.num_commands());

    // Here I restore the original version of the mission (in case it should be reloaded)
    gcs_send_text_fmt(PSTR("Restoring original mission"));
    AP_Mission::Mission_Command wp;
    uint16_t num_commands = mission.num_commands();
    gcs_send_text_fmt(PSTR("Number of commands: %d"),num_commands);
    mission.get_next_nav_cmd(num_commands-1, wp);
    uint16_t landing_wp_index = wp.index;
    gcs_send_text_fmt(PSTR("L_WP index: %d"),landing_wp_index);

    // If the last command is the landing
    if(wp.id==MAV_CMD_NAV_LAND)
    {
	// I remove the three previous commands (virtual waypoints)
	uint16_t start = num_commands-4;
	gcs_send_text_fmt(PSTR("Truncate mission at index: %d"),start);
	mission.truncate(start);
	gcs_send_text_fmt(PSTR("Num comm after truncate: %d"),mission.num_commands());
	gcs_send_text_fmt(PSTR("Re-adding landing WP"));
	// then, I re-add the landing waypoint
	mission.add_cmd(wp);
	gcs_send_text_fmt(PSTR("Num comm after re-adding L_WP: %d"),mission.num_commands());
	// I update the mission
	mission.update();
    }
}


void Plane::log_perf_info()
{
    if (scheduler.debug() != 0) {
        gcs_send_text_fmt(PSTR("G_Dt_max=%lu G_Dt_min=%lu\n"), 
                          (unsigned long)G_Dt_max, 
                          (unsigned long)G_Dt_min);
    }
#if HAL_CPU_CLASS >= HAL_CPU_CLASS_75
    if (should_log(MASK_LOG_PM))
        Log_Write_Performance();
#endif
    G_Dt_max = 0;
    G_Dt_min = 0;
    resetPerfData();
}

void Plane::compass_save()
{
    if (g.compass_enabled) {
        compass.save_offsets();
    }
}

void Plane::terrain_update(void)
{
#if AP_TERRAIN_AVAILABLE
    terrain.update();

    // tell the rangefinder our height, so it can go into power saving
    // mode if available
    float height;
    if (terrain.height_above_terrain(height, true)) {
        rangefinder.set_estimated_terrain_height(height);
    }
#endif
}

void Plane::dataflash_periodic(void)
{
    DataFlash.periodic_tasks();
}

/*
  once a second update the airspeed calibration ratio
 */
void Plane::airspeed_ratio_update(void)
{
    if (!airspeed.enabled() ||
        gps.status() < AP_GPS::GPS_OK_FIX_3D ||
        gps.ground_speed() < 4) {
        // don't calibrate when not moving
        return;        
    }
    if (airspeed.get_airspeed() < aparm.airspeed_min && 
        gps.ground_speed() < (uint32_t)aparm.airspeed_min) {
        // don't calibrate when flying below the minimum airspeed. We
        // check both airspeed and ground speed to catch cases where
        // the airspeed ratio is way too low, which could lead to it
        // never coming up again
        return;
    }
    if (labs(ahrs.roll_sensor) > roll_limit_cd ||
        ahrs.pitch_sensor > aparm.pitch_limit_max_cd ||
        ahrs.pitch_sensor < pitch_limit_min_cd) {
        // don't calibrate when going beyond normal flight envelope
        return;
    }
    const Vector3f &vg = gps.velocity();
    airspeed.update_calibration(vg);
    gcs_send_airspeed_calibration(vg);
}


/*
  read the GPS and update position
 */
void Plane::update_GPS_50Hz(void)
{
    static uint32_t last_gps_reading[GPS_MAX_INSTANCES];
    gps.update();

    for (uint8_t i=0; i<gps.num_sensors(); i++) {
        if (gps.last_message_time_ms(i) != last_gps_reading[i]) {
            last_gps_reading[i] = gps.last_message_time_ms(i);
            if (should_log(MASK_LOG_GPS)) {
                Log_Write_GPS(i);
            }
        }
    }
}

/*
  read update GPS position - 10Hz update
 */
void Plane::update_GPS_10Hz(void)
{
    // get position from AHRS
    have_position = ahrs.get_position(current_loc);

    static uint32_t last_gps_msg_ms;
    if (gps.last_message_time_ms() != last_gps_msg_ms && gps.status() >= AP_GPS::GPS_OK_FIX_3D) {
        last_gps_msg_ms = gps.last_message_time_ms();

        if (ground_start_count > 1) {
            ground_start_count--;
        } else if (ground_start_count == 1) {
            // We countdown N number of good GPS fixes
            // so that the altitude is more accurate
            // -------------------------------------
            if (current_loc.lat == 0) {
                ground_start_count = 5;

            } else {
                init_home();

                // set system clock for log timestamps
                hal.util->set_system_clock(gps.time_epoch_usec());

                if (g.compass_enabled) {
                    // Set compass declination automatically
                    const Location &loc = gps.location();
                    compass.set_initial_location(loc.lat, loc.lng);
                }
                ground_start_count = 0;
            }
        }

        // see if we've breached the geo-fence
        geofence_check(false);

#if CAMERA == ENABLED
        if (camera.update_location(current_loc) == true) {
            do_take_picture();
        }
#endif        

        if (!hal.util->get_soft_armed()) {
            update_home();
        }

        // update wind estimate
        ahrs.estimate_wind();
    }

    calc_gndspeed_undershoot();
}

/*
  main handling for AUTO mode
 */
void Plane::handle_auto_mode(void)
{
    uint8_t nav_cmd_id;

    // we should be either running a mission or RTLing home
    if (mission.state() == AP_Mission::MISSION_RUNNING) {
        nav_cmd_id = mission.get_current_nav_cmd().id;
    }else{
        nav_cmd_id = auto_rtl_command.id;
    }

    if (nav_cmd_id == MAV_CMD_NAV_TAKEOFF ||
        (nav_cmd_id == MAV_CMD_NAV_LAND && flight_stage == AP_SpdHgtControl::FLIGHT_LAND_ABORT)) {
        takeoff_calc_roll();
        takeoff_calc_pitch();
        calc_throttle();
    } else if (nav_cmd_id == MAV_CMD_NAV_LAND) {
        calc_nav_roll();
        calc_nav_pitch();
        
        if (auto_state.land_complete) {
            // during final approach constrain roll to the range
            // allowed for level flight
            nav_roll_cd = constrain_int32(nav_roll_cd, -g.level_roll_limit*100UL, g.level_roll_limit*100UL);
        }
        calc_throttle();
        
        if (auto_state.land_complete) {
            // we are in the final stage of a landing - force
            // zero throttle
            channel_throttle->servo_out = 0;
        }
    } else {
        // we are doing normal AUTO flight, the special cases
        // are for takeoff and landing
        if (nav_cmd_id != MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT) {
            steer_state.hold_course_cd = -1;
        }

	//if you are in Loiter Unlim, you can change the loiter altitude by pitch stick
	if (nav_cmd_id == MAV_CMD_NAV_LOITER_UNLIM)
	    update_loiter_unlim_height();

        auto_state.land_complete = false;
        calc_nav_roll();
        calc_nav_pitch();
        calc_throttle();
    }
}

/*
  main flight mode dependent update code 
 */
void Plane::update_flight_mode(void)
{
    enum FlightMode effective_mode = control_mode;
    if (control_mode == AUTO && g.auto_fbw_steer) {
        effective_mode = FLY_BY_WIRE_A;
    }

    if (effective_mode != AUTO) {
        // hold_course is only used in takeoff and landing
        steer_state.hold_course_cd = -1;
    }

    switch (effective_mode) 
    {
    case AUTO:
        handle_auto_mode();
        break;

    case RTL:
    case LOITER:
    case GUIDED:
	update_loiter_unlim_height();
        calc_nav_roll();
        calc_nav_pitch();
        calc_throttle();
        break;
        
    case TRAINING: {
        training_manual_roll = false;
        training_manual_pitch = false;
        update_load_factor();
        
        // if the roll is past the set roll limit, then
        // we set target roll to the limit
        if (ahrs.roll_sensor >= roll_limit_cd) {
            nav_roll_cd = roll_limit_cd;
        } else if (ahrs.roll_sensor <= -roll_limit_cd) {
            nav_roll_cd = -roll_limit_cd;                
        } else {
            training_manual_roll = true;
            nav_roll_cd = 0;
        }
        
        // if the pitch is past the set pitch limits, then
        // we set target pitch to the limit
        if (ahrs.pitch_sensor >= aparm.pitch_limit_max_cd) {
            nav_pitch_cd = aparm.pitch_limit_max_cd;
        } else if (ahrs.pitch_sensor <= pitch_limit_min_cd) {
            nav_pitch_cd = pitch_limit_min_cd;
        } else {
            training_manual_pitch = true;
            nav_pitch_cd = 0;
        }
        if (fly_inverted()) {
            nav_pitch_cd = -nav_pitch_cd;
        }
        break;
    }

    case ACRO: {
        // handle locked/unlocked control
        if (acro_state.locked_roll) {
            nav_roll_cd = acro_state.locked_roll_err;
        } else {
            nav_roll_cd = ahrs.roll_sensor;
        }
        if (acro_state.locked_pitch) {
            nav_pitch_cd = acro_state.locked_pitch_cd;
        } else {
            nav_pitch_cd = ahrs.pitch_sensor;
        }
        break;
    }

    case AUTOTUNE:
    case FLY_BY_WIRE_A: {
        // set nav_roll and nav_pitch using sticks
        nav_roll_cd  = channel_roll->norm_input() * roll_limit_cd;
        nav_roll_cd = constrain_int32(nav_roll_cd, -roll_limit_cd, roll_limit_cd);
        update_load_factor();
        float pitch_input = channel_pitch->norm_input();
        if (pitch_input > 0) {
            nav_pitch_cd = pitch_input * aparm.pitch_limit_max_cd;
        } else {
            nav_pitch_cd = -(pitch_input * pitch_limit_min_cd);
        }
        adjust_nav_pitch_throttle();
        nav_pitch_cd = constrain_int32(nav_pitch_cd, pitch_limit_min_cd, aparm.pitch_limit_max_cd.get());
        if (fly_inverted()) {
            nav_pitch_cd = -nav_pitch_cd;
        }
        if (failsafe.ch3_failsafe && g.short_fs_action == 2) {
            // FBWA failsafe glide
            nav_roll_cd = 0;
            nav_pitch_cd = 0;
            channel_throttle->servo_out = 0;
        }
        if (g.fbwa_tdrag_chan > 0) {
            // check for the user enabling FBWA taildrag takeoff mode
            bool tdrag_mode = (hal.rcin->read(g.fbwa_tdrag_chan-1) > 1700);
            if (tdrag_mode && !auto_state.fbwa_tdrag_takeoff_mode) {
                if (auto_state.highest_airspeed < g.takeoff_tdrag_speed1) {
                    auto_state.fbwa_tdrag_takeoff_mode = true;
                    gcs_send_text_P(MAV_SEVERITY_WARNING, PSTR("FBWA tdrag mode\n"));
                }
            }
        }
        break;
    }

    case FLY_BY_WIRE_B:
        // Thanks to Yury MonZon for the altitude limit code!
        nav_roll_cd = channel_roll->norm_input() * roll_limit_cd;
        nav_roll_cd = constrain_int32(nav_roll_cd, -roll_limit_cd, roll_limit_cd);
        update_load_factor();
        update_fbwb_speed_height();
        break;

    case FLY_BY_WIRE_C: {
        nav_roll_cd = channel_roll->norm_input() * roll_limit_cd;
        nav_roll_cd = constrain_int32(nav_roll_cd, -roll_limit_cd, roll_limit_cd);
        update_load_factor();

	set_target_altitude_current(); // no altitude control
        update_fbwc_speed(); // output demanded throttle based on airspeed

	//directly output pilot's pitch
	float pitch_input = channel_pitch->norm_input();
        if (pitch_input > 0) {
            nav_pitch_cd = pitch_input * aparm.pitch_limit_max_cd;
        } else {
            nav_pitch_cd = -(pitch_input * pitch_limit_min_cd);
        }
        //adjust_nav_pitch_throttle();
        nav_pitch_cd = constrain_int32(nav_pitch_cd, pitch_limit_min_cd, aparm.pitch_limit_max_cd.get());
        if (fly_inverted()) {
            nav_pitch_cd = -nav_pitch_cd;
        }
        if (failsafe.ch3_failsafe && g.short_fs_action == 2) {
            // FBWC failsafe glide
            nav_roll_cd = 0;
            nav_pitch_cd = 0;
            channel_throttle->servo_out = 0;
        }
        break;
    }
    case CRUISE:
        /*
          in CRUISE mode we use the navigation code to control
          roll when heading is locked. Heading becomes unlocked on
          any aileron or rudder input
        */
        if ((channel_roll->control_in != 0 ||
             rudder_input != 0)) {                
            cruise_state.locked_heading = false;
            cruise_state.lock_timer_ms = 0;
        }                 
        
        if (!cruise_state.locked_heading) {
            nav_roll_cd = channel_roll->norm_input() * roll_limit_cd;
            nav_roll_cd = constrain_int32(nav_roll_cd, -roll_limit_cd, roll_limit_cd);
            update_load_factor();
        } else {
            calc_nav_roll();
        }
        update_fbwb_speed_height();
        break;
        
    case STABILIZE:
        nav_roll_cd        = 0;
        nav_pitch_cd       = 0;
        // throttle is passthrough
        break;
        
    case CIRCLE:
        // we have no GPS installed and have lost radio contact
        // or we just want to fly around in a gentle circle w/o GPS,
        // holding altitude at the altitude we set when we
        // switched into the mode
        nav_roll_cd  = roll_limit_cd / 3;
        update_load_factor();
        calc_nav_pitch();
        calc_throttle();
        break;

    case MANUAL:
        // servo_out is for Sim control only
        // ---------------------------------
        channel_roll->servo_out = channel_roll->pwm_to_angle();
        channel_pitch->servo_out = channel_pitch->pwm_to_angle();
        steering_control.steering = steering_control.rudder = channel_rudder->pwm_to_angle();
        break;
        //roll: -13788.000,  pitch: -13698.000,   thr: 0.000, rud: -13742.000
        
    case INITIALISING:
        // handled elsewhere
        break;
    }
}

void Plane::update_navigation()
{
    // wp_distance is in ACTUAL meters, not the *100 meters we get from the GPS
    // ------------------------------------------------------------------------

    // distance and bearing calcs only
    switch(control_mode) {
    case AUTO:
        update_commands();
        break;
            
    case RTL:
        if (g.rtl_autoland == 1 &&
            !auto_state.checked_for_autoland &&
            nav_controller->reached_loiter_target() && 
            labs(altitude_error_cm) < 1000) {
            // we've reached the RTL point, see if we have a landing sequence
            jump_to_landing_sequence();

            // prevent running the expensive jump_to_landing_sequence
            // on every loop
            auto_state.checked_for_autoland = true;
        }
        else if (g.rtl_autoland == 2 &&
            !auto_state.checked_for_autoland) {
            // Go directly to the landing sequence
            jump_to_landing_sequence();

            // prevent running the expensive jump_to_landing_sequence
            // on every loop
            auto_state.checked_for_autoland = true;
        }
        // fall through to LOITER

    case LOITER:
    case GUIDED:
        // allow loiter direction to be changed in flight
        if (g.loiter_radius < 0) {
            loiter.direction = -1;
        } else {
            loiter.direction = 1;
        }
        update_loiter();
        break;

    case CRUISE:
        update_cruise();
        break;

    case MANUAL:
    case STABILIZE:
    case TRAINING:
    case INITIALISING:
    case ACRO:
    case FLY_BY_WIRE_A:
    case AUTOTUNE:
    case FLY_BY_WIRE_B:
    case FLY_BY_WIRE_C:
    case CIRCLE:
        // nothing to do
        break;
    }
}

/*
  set the flight stage
 */
void Plane::set_flight_stage(AP_SpdHgtControl::FlightStage fs) 
{
    if (fs == flight_stage) {
        return;
    }

    switch (fs) {
    case AP_SpdHgtControl::FLIGHT_LAND_APPROACH:
#if GEOFENCE_ENABLED == ENABLED 
        if (g.fence_autoenable == 1) {
            if (! geofence_set_enabled(false, AUTO_TOGGLED)) {
                gcs_send_text_P(MAV_SEVERITY_CRITICAL, PSTR("Disable fence failed (autodisable)"));
            } else {
                gcs_send_text_P(MAV_SEVERITY_CRITICAL, PSTR("Fence disabled (autodisable)"));
            }
        } else if (g.fence_autoenable == 2) {
            if (! geofence_set_floor_enabled(false)) {
                gcs_send_text_P(MAV_SEVERITY_CRITICAL, PSTR("Disable fence floor failed (autodisable)"));
            } else {
                gcs_send_text_P(MAV_SEVERITY_CRITICAL, PSTR("Fence floor disabled (auto disable)"));
            }
        }
#endif
        break;

    case AP_SpdHgtControl::FLIGHT_LAND_ABORT:
        gcs_send_text_fmt(PSTR("Landing aborted via throttle, climbing to %dm"), auto_state.takeoff_altitude_rel_cm/100);
        break;

    case AP_SpdHgtControl::FLIGHT_LAND_FINAL:
    case AP_SpdHgtControl::FLIGHT_NORMAL:
    case AP_SpdHgtControl::FLIGHT_TAKEOFF:
        break;
    }
    

    flight_stage = fs;
}

void Plane::update_alt()
{
    barometer.update();
    if (should_log(MASK_LOG_IMU)) {
        Log_Write_Baro();
    }

    // calculate the sink rate.
    float sink_rate;
    Vector3f vel;
    if (ahrs.get_velocity_NED(vel)) {
        sink_rate = vel.z;
    } else if (gps.status() >= AP_GPS::GPS_OK_FIX_3D && gps.have_vertical_velocity()) {
        sink_rate = gps.velocity().z;
    } else {
        sink_rate = -barometer.get_climb_rate();        
    }

    // low pass the sink rate to take some of the noise out
    auto_state.sink_rate = 0.8f * auto_state.sink_rate + 0.2f*sink_rate;
    
    geofence_check(true);

    update_flight_stage();
}

/*
  recalculate the flight_stage
 */
void Plane::update_flight_stage(void)
{
    // Update the speed & height controller states
    if (auto_throttle_mode && !throttle_suppressed) {        
        if (control_mode==AUTO) {
            if (auto_state.takeoff_complete == false) {
                set_flight_stage(AP_SpdHgtControl::FLIGHT_TAKEOFF);
            } else if (mission.get_current_nav_cmd().id == MAV_CMD_NAV_LAND) {

                if ((g.land_abort_throttle_enable && channel_throttle->control_in > 95) ||
                        flight_stage == AP_SpdHgtControl::FLIGHT_LAND_ABORT){
                    // abort mode is sticky, it must complete while executing NAV_LAND
                    set_flight_stage(AP_SpdHgtControl::FLIGHT_LAND_ABORT);
                } else if (auto_state.land_complete == true) {
                    set_flight_stage(AP_SpdHgtControl::FLIGHT_LAND_FINAL);
                } else {
                    set_flight_stage(AP_SpdHgtControl::FLIGHT_LAND_APPROACH);
                }

            } else {
                set_flight_stage(AP_SpdHgtControl::FLIGHT_NORMAL);
            }
        } else {
            set_flight_stage(AP_SpdHgtControl::FLIGHT_NORMAL);
        }

        SpdHgt_Controller->update_pitch_throttle(relative_target_altitude_cm(),
                                                 target_airspeed_cm,
                                                 flight_stage,
                                                 auto_state.takeoff_pitch_cd,
                                                 throttle_nudge,
                                                 tecs_hgt_afe(),
                                                 aerodynamic_load_factor);
	/*
	gcs_send_text_fmt(PSTR("throttle %ld, nav_pit %2.3f, out_pit %2.3f"),
                                        SpdHgt_Controller->get_throttle_demand(),
					nav_pitch_cd/100.0f,
					channel_pitch->servo_out/100.0f);
					*/
        if (should_log(MASK_LOG_TECS)) {
            Log_Write_TECS_Tuning();
        }
    }

    // tell AHRS the airspeed to true airspeed ratio
    airspeed.set_EAS2TAS(barometer.get_EAS2TAS());
}




#if OPTFLOW == ENABLED
// called at 50hz
void Plane::update_optical_flow(void)
{
    static uint32_t last_of_update = 0;

    // exit immediately if not enabled
    if (!optflow.enabled()) {
        return;
    }

    // read from sensor
    optflow.update();

    // write to log and send to EKF if new data has arrived
    if (optflow.last_update() != last_of_update) {
        last_of_update = optflow.last_update();
        uint8_t flowQuality = optflow.quality();
        Vector2f flowRate = optflow.flowRate();
        Vector2f bodyRate = optflow.bodyRate();
        ahrs.writeOptFlowMeas(flowQuality, flowRate, bodyRate, last_of_update);
        Log_Write_Optflow();
    }
}
#endif

/*
  compatibility with old pde style build
 */
void setup(void);
void loop(void);

void setup(void)
{
    plane.setup();
}
void loop(void)
{
    plane.loop();
}

AP_HAL_MAIN();
