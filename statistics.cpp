/**
 * File: statistics.cpp
 * \brief this class calculates the statistics of the training
 * 
 *        This class calculate the average speed, the consumed calories and 
 *        the time in seconds for the training
 * \author Omar Scotti
 * \author Diego Rondelli
 * \date 21/01/2014
 * \version 1.0
 */

#include <cstdio>
#include "miosix.h"
#include "lis302dl.h"
#include "statistics.h"
#include "pedometer.h"
#include <math.h>

using namespace std;
using namespace miosix;


float avg;
int oldSteps;
float cal;
float distance;
int seconds;
int stepsInInterval;
int height;
Pedometer* pedometer;
float multParam;
bool moving;

bool Statistics::instanceFlag = false;
Statistics* Statistics::statistics = NULL;

/**
 * Private class constructor
 */
Statistics::Statistics(){
    
    pedometer = Pedometer::getInstance();
    avg=0;
    oldSteps = pedometer->getStep();
    cal=0;
    distance=0;
    seconds=0;
    stepsInInterval=0;
    height=170; //=getHeight(); from the interface module.
    multParam=1;
    moving=false;
}

/**
 * \brief Factory patten 
 * \details Factory pattern guarantees that in all the program only one object
 *          with type Utility exists. To make this the constructor is private
 *          and is substituted by this method
 * @param void
 * @returns the only existing instance of Statistics 
 */
Statistics* Statistics::getInstance()
{
    if(! instanceFlag)
    {
        statistics = new Statistics();
        instanceFlag = true;
        return statistics;
    }
    else
    {
        return statistics;
    }
}

/**
 * \brief starts the statistic calc
 * \details calculates the activity time in seconds, the average speed and the 
 *          distance.
 */

void Statistics::start(){
    while(true){
    usleep(2000);
    stepsInInterval = (pedometer->getStep()-oldSteps);

    switch(stepsInInterval){
            
        case (0): 
            moving=false;
            break;
            
        case (1): 
            moving=true;
            multParam=5;
            break;
        case (2): 
            moving=true;
            multParam=5;
            break;
        case (3):
            moving=true;
            multParam=5;
            break;
        case (4):
            moving=true;
            multParam=3;
            break;
        case (5):
            moving=true;
            multParam=2;
            break;
        case(6):
            moving=true;
            multParam=1.2;
            break;
        case(7):
            moving=true;
            multParam=1;
            break;
        default:
            moving=true;
            multParam=(1/1.2);
    }
                    
    if(moving){
        avg=((avg*seconds)+(height*2/multParam)/(seconds+2));
        seconds+=2;
        distance+=height*2/multParam;
    } 
   }
}

/**
 * getter of average speed
 * @return the average speed 
 */
float Statistics::getAvg(){
    return avg;
}
/**
 * getter of distance traveled
 * @return distance traveled
 */
float Statistics::getDistance(){
    return distance;
}
/**
 * getter of walking time
 * @return time of walking in seconds
 */
int Statistics::getTime(){
    return seconds;
}