/* 
 * File:   pedometer.cpp
 *  \brief     INTRO VELOCE
 *  \details   DETTAGLI
 *  \author    Omar Scotti
 *  \author    Diego Rondelli
 *  \version   1.0
 *  \date      10/01/2014
 */

#include <cstdio>
#include "miosix.h"
#include "lis302dl.h"
#include "pedometer.h"
#include "utility.h"

#define LIMIT 120
#define SOUND_FREQUENCY 50

using namespace std;
using namespace miosix;

typedef enum
   {
   onPause = 0,
   onMove  = 1
    } tState ;

int step=0;
unsigned Sensitivity = LIMIT, old_Sensitivity = 0, Hysteresis = LIMIT/4, old_Hysteresis = 0;
int16_t x, y, z;
Lis302dl lis302dl;
tState currentState= onPause;
Utility* utility_p;

Pedometer::Pedometer(){
    utility_p=Utility::getInstance();
}

void Pedometer::start(){
   
    lis302dl.memsConfig();
    
    while(true){
        utility_p->ledBlue();
        takeAverage();
        utility_p->ledRed();
        //writeData();
        stepCounter();
        utility_p->ledRed();
        }
}

void Pedometer::stepCounter(){
        
        //Step are considered as linked to fast variation of the acceleration.
        //We first evaluate the variation (dx/dy/dz) by substracting the current
        //values given by the MEMS to an 'older' value, in fact another average value 
        //done with more value (longer time constant).
        //delta_x = average on last 4 value, minus average done on last 16 value
        unsigned dx =  average4.x - average16.x ; 
        unsigned dy =  average4.y - average16.y ; 
        unsigned dz =  average4.z - average16.z ; 
        long unsigned test = ( dx*dx + dy*dy + dz*dz ) / 64 ;       
        // amplitude of the delta is calculated as the sum of the squares.

        //Now we switch from the 'OnMove' state to 'On Pause' (and vice versa) with a small hysteresis
        if ( (test< (Sensitivity - (Hysteresis/2) ) ) && (currentState == onMove) )
                {
                step++;
                utility_p->ledBlue();
                currentState = onPause;
                }
        else if ( (test>=Sensitivity + (Hysteresis/2) ) && (currentState == onPause) )
                {
                currentState = onMove;
                }
}

void Pedometer::takeAverage(){
    lis302dl.getMemsData(&x,&y,&z);
    utility_p->ledGreen();
    average(&average4,4);
    average(&average16,16);
}

void Pedometer::average(Average* average,int num){
    average->x=(average->x*(num-1)+x)/num;
    average->y=(average->y*(num-1)+y)/num;
    average->z=(average->z*(num-1)+y)/num;
}

void Pedometer::incrementStep(){
    step++;
    //if(!(step%50)) evviva(step);
}

int Pedometer::getStep(){
    return step;
}