#include <stdio.h>
#include "AP_MissionCheck_VWP.h"

MissionCheck_VWP::MissionCheck_VWP(AP_Mission &mission, DataFlash_Class &dataflash, VirtualWP &virtual_wp): MissionCheck(mission), _dataflash(dataflash), _virtualwp(virtual_wp)
{
    vwp_feature_usable = true;
}

void MissionCheck_VWP::init_mission()
{
    asprintf(&msg,"INIT VWP Mission");
    logInfo(msg);
    _virtualwp.init();
}

void MissionCheck_VWP::logInfo(char* _msg)
{
    GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, PSTR(_msg));
    _dataflash.Log_Write_Message_P(PSTR(_msg));
}

void MissionCheck_VWP::notify_user()
{
    // The idea of this function is to drive the LED to notify the USER about possible errors
}

char* MissionCheck_VWP::get_mission_type()
{
    char* mission_type;
    asprintf(&mission_type,"VWP");
    return mission_type;

}

bool MissionCheck_VWP::check()
{
    
    // Here I check the basic requirements for using the VWP feature
  
    if(!is_takeoff_wp_present())
    {
	vwp_feature_usable = false;
	asprintf(&msg,"TAKEOFF WP NOT PRESENT");
	logInfo(msg);
    }
       
    if(!is_landing_wp_present())
    {
	vwp_feature_usable = false;
	asprintf(&msg,"LANDING WP NOT PRESENT");
	logInfo(msg);
    }
    
    asprintf(&msg,"Num Nav WP: %d",get_num_nav_wayponts());
    logInfo(msg);
    
    if(get_num_nav_wayponts() < 3)
    {
	vwp_feature_usable = false;
	asprintf(&msg,"AT LEAST 3 NAV WPS REQUIRED");
	logInfo(msg);
    }
    
    return vwp_feature_usable;
  
}