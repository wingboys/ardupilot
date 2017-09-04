/*
 * AP_MissionCheck.cpp
 *
 *  Created on: August 10, 2017
 *      Author: Alessandro Benini
 */

#include <stdio.h>
#include "AP_MissionCheck.h"

MissionCheck::MissionCheck(AP_Mission& mission):
	_mission(mission)
{
    takeoff_wp_present = false;
    landing_wp_present = false;
    num_nav_wayponts = 0;
    
    inspect_stored_mission();
}

void MissionCheck::inspect_stored_mission()
{
  
  AP_Mission::Mission_Command cmd;
  
  uint16_t num_items = _mission.num_commands();
  
  for(uint16_t i = 0; i < num_items; i++)
  {
      _mission.get_next_nav_cmd(i, cmd);
      
      if(cmd.id == MAV_CMD_NAV_TAKEOFF)
	takeoff_wp_present = true;
      
      if(cmd.id == MAV_CMD_NAV_LAND)
	landing_wp_present = true;
      
      // I check if index is greater than 0 to avoid counting the home waypoint
      if(cmd.id == MAV_CMD_NAV_WAYPOINT && cmd.index > 0)
	++num_nav_wayponts;  
     
  }

}

int16_t MissionCheck::get_index_landing_WP()
{
    // Get the number of commands for the current mission
    int16_t num_cmd = _mission.num_commands();

    // Stores the current cmd item
    AP_Mission::Mission_Command current_cmd;

    // Start iterating from the end of the mission
    for(int16_t i=num_cmd-1; i>=0; i--)
    {
	_mission.get_next_nav_cmd(i, current_cmd);
	// If the current command is a NAV command
	if(current_cmd.id == MAV_CMD_NAV_LAND)
	return current_cmd.index;
    }

    // If I ended the for loop and the return value is -1, it means that the current mission has no
    // landing waypoints.
    return -1;
}

int16_t MissionCheck::get_index_last_nav_WP()
{
    // Get the number of commands for the current mission
    int16_t num_cmd = _mission.num_commands();

    // Stores the current cmd item
    AP_Mission::Mission_Command current_cmd;

    // Start iterating from the end of the mission, looking for the n-th last DO_NAV waypoint.
    for(int16_t i=num_cmd-1; i>=0; i--)
    {
	_mission.get_next_nav_cmd(i, current_cmd);
	// If the current command is a NAV command
	if(current_cmd.id == MAV_CMD_NAV_WAYPOINT)
	return current_cmd.index;
    }

    // If I ended the for loop and the return value is -1, it means that the current mission has no
    // navigation waypoints.
    return -1;
}
