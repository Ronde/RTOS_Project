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
#include "serial.h"

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
SerialPort serial;
tState currentState= onPause;
typedef Gpio<GPIOD_BASE,15> blueLed;
typedef Gpio<GPIOD_BASE,14> redLed;
typedef Gpio<GPIOD_BASE,12> greenLed;

Pedometer::Pedometer(){}

void Pedometer::start(){
    
    //Set led in output
    blueLed::mode(Mode::OUTPUT);
    redLed::mode(Mode::OUTPUT);
    greenLed::mode(Mode::OUTPUT);
   
    lis302dl.memsConfig();
    
    while(true){
        ledBlue();
        takeAverage();
        ledRed();
        //writeData();
        stepCounter();
        ledRed();
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
                ledBlue();
                currentState = onPause;
                }
        else if ( (test>=Sensitivity + (Hysteresis/2) ) && (currentState == onPause) )
                {
                currentState = onMove;
                }
}

void Pedometer::takeAverage(){
    lis302dl.getMemsData(&x,&y,&z);
    ledGreen();
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

void Pedometer::ledBlue(){
    blueLed::high();
    usleep(1000000);
    blueLed::low();
    usleep(1000000);
}

void Pedometer::ledRed(){
    redLed::high();
    usleep(1000000);
    redLed::low();
    usleep(1000000);
}

void Pedometer::ledGreen(){
    greenLed::high();
    usleep(1000000);
    greenLed::low();
    usleep(1000000);
}