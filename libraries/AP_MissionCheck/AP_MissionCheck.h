/*
 * AP_MissionCheck.h
 *
 *  Created on: August 10, 2017
 *      Author: Alessandro Benini
 */

#ifndef AP_MISSIONCHECK_H_
#define AP_MISSIONCHECK_H_

#include <AP_Mission/AP_Mission.h>

class MissionCheck
{
  
public:

    // Constructor
    MissionCheck(AP_Mission &mission);

    // Destructor
    ~MissionCheck() {}
    
    // Inspect if a mission is loaded at startup. Returns true if we have a takeoff waypoint, a landing waypoint and at least one mission waypoint.
    // This could be a virtual function that should be implemented by the user
    void inspect_stored_mission();
    
    bool is_takeoff_wp_present() { return takeoff_wp_present; }
    bool is_landing_wp_present() { return landing_wp_present; }
    uint16_t get_num_nav_wayponts() { return num_nav_wayponts; }
    
    // TODO: Implement a virtual method for checking the class
    virtual void check() = 0;

protected:

    bool	takeoff_wp_present;
    bool 	landing_wp_present;
    uint16_t	num_nav_wayponts;
    
private:
  
    /// get_index_last_nav_WP - returns the index of the last mission waypoint.
    int16_t get_index_last_nav_WP();

    /// get_index_landing_WP - returns the index of the landing waypoint. The landing waypoint
    /// should always be the last item. But this function is implemented in order to contemplate
    /// the case where further actions are programmed after the landing and/or to make sure that
    /// a landing waypoint is set.
    int16_t get_index_landing_WP();

    /// get_index_for_VWP_generation - return the index of the nav cmd item after which the vwp will be generated (referred to as CMD_VWP)
    /// returns 0 if the mission is shorter than the distance between landing waypoint and CMD_VWP
    // int16_t get_index_for_VWP_generation(int16_t n);

    AP_Mission&		_mission;
};

#endif