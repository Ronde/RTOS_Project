/* 
 * File:   utility.cpp
 *  \brief     INTRO VELOCE
 *  \details   DETTAGLI
 *  \author    Omar Scotti
 *  \author    Diego Rondelli
 *  \version   1.0
 *  \date      16/01/2014
 */

#include "utility.h"
#include <iostream>
#include <cstdio>
#include "miosix.h"
#include <string.h>

using namespace std;
using namespace miosix;

bool Utility::instanceFlag = false;
Utility* Utility::utility = NULL;
typedef Gpio<GPIOD_BASE,15> blueLed;
typedef Gpio<GPIOD_BASE,14> redLed;
typedef Gpio<GPIOD_BASE,12> greenLed;

Utility::Utility(){
    blueLed::mode(Mode::OUTPUT);
    redLed::mode(Mode::OUTPUT);
    greenLed::mode(Mode::OUTPUT);
    
}

Utility* Utility::getInstance()
{
    if(! instanceFlag)
    {
        utility = new Utility();
        instanceFlag = true;
        return utility;
    }
    else
    {
        return utility;
    }
}

void Utility::ledBlue(){
    blueLed::high();
    usleep(1000000);
    blueLed::low();
    usleep(1000000);
}

void Utility::ledRed(){
    redLed::high();
    usleep(1000000);
    redLed::low();
    usleep(1000000);
}

void Utility::ledGreen(){
    greenLed::high();
    usleep(1000000);
    greenLed::low();
    usleep(1000000);
}

void Utility::test(int16_t x,int16_t y,int16_t z,int step,long unsigned test){
    
    printf("x: %i\t",x);
    printf("y: %i\t",y);
    printf("z: %i\t",z);
    printf("step: %i\t",step);
    printf("test: %i\n",test);
    
}