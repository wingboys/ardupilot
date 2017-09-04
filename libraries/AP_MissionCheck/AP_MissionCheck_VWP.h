/*
 * AP_MissionCheck_VWP.h
 *
 *  Created on: August 10, 2017
 *      Author: Alessandro Benini
 */

#ifndef AP_MISSIONCHECK_VWP_H_
#define AP_MISSIONCHECK_VWP_H_

#include <GCS_MAVLink/GCS.h>
#include <DataFlash/DataFlash.h>
#include <AP_VirtualWP/AP_VirtualWP.h>

#include "AP_MissionCheck.h"

class MissionCheck_VWP : public MissionCheck
{
  
public:
  
    MissionCheck_VWP(AP_Mission &mission, DataFlash_Class &dataflash, VirtualWP &virtual_wp);
    
    void init_mission();
    bool check();
    void notify_user();
    char* get_mission_type();
     
private:
    
    DataFlash_Class&	_dataflash;
    VirtualWP&		_virtualwp;
    bool vwp_feature_usable;
    // Generic message container for logging
    char* msg;
    
    void logInfo(char* _msg);
  
};

#endif