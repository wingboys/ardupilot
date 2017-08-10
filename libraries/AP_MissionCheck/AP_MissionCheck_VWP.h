/*
 * AP_MissionCheck_VWP.h
 *
 *  Created on: June 06, 2017
 *      Author: Alessandro Benini
 */

#ifndef AP_MISSIONCHECK_VWP_H_
#define AP_MISSIONCHECK_VWP_H_

#include "AP_MissionCheck.h"

class MissionCheck_VWP : public MissionCheck
{
  
public:
  
    MissionCheck_VWP(AP_Mission &mission) : MissionCheck(mission) {}
    
    uint16_t get_index_virtual_wp() { return index_virtual_wp; }
    void init();
    
    void check();
     
private:
    uint16_t index_virtual_wp;
  
};

#endif