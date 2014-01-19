/**
 * File:   pedometer.cpp
 *  \brief     This class contains the logic to understand if a movement is a step
 *             or not

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
#include <math.h>

#define LIMIT  120

using namespace std;
using namespace miosix;

/**
 * Defines the state of the counter
 */
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

/**
 * Class constructor
 */
Pedometer::Pedometer(){
    utility_p=Utility::getInstance();
    
    average4.x=0;
    average4.y=0;
    average4.z=0;
    average16.x=0;
    average16.y=0;
    average16.z=0;
    
    for(int i=0;i<16;i++){
        data.lastDataX[i]=0;
        data.lastDataY[i]=0;
        data.lastDataZ[i]=0;
    }
}

/**
 * Starts the step counting
 * @param void
 * @returns void
 */
void Pedometer::start(){
    
    utility_p->ledGreen();
    
    lis302dl.memsConfig();
    
    utility_p->ledRed();
            
    while(true){
        
        takeAverage();
        
        stepCounter();
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
                incrementStep();
                currentState = onPause;
                }
        else if ( (test>=Sensitivity + (Hysteresis/2) ) && (currentState == onPause))
                {
                currentState = onMove;
                }
        
        utility_p->test(dx,dy,dz,step,test);
        
}

void Pedometer::takeAverage(){
    lis302dl.getMemsData(&x,&y,&z);
    updateData();
    average(&average4,4);
    average(&average16,16);
}

void Pedometer::updateData(){
    
    /*Shift a destra*/
    for(int i=15;i>0;i--){
        data.lastDataX[i]=data.lastDataX[i-1];
        data.lastDataY[i]=data.lastDataY[i-1];
        data.lastDataZ[i]=data.lastDataZ[i-1];
    }
    
    /*Aggiunta nuovo dato*/
    data.lastDataX[0]=x;
    data.lastDataY[0]=y;
    data.lastDataZ[0]=z;
}

void Pedometer::average(Average* average,int num){
    int sumX=0,sumY=0,sumZ=0;
    
    /*Somma*/
    for(int i=0;i<num;i++){
        sumX +=data.lastDataX[i];
        sumY +=data.lastDataY[i];
        sumZ +=data.lastDataZ[i];
    }
    
    /*Media*/
    float averageXf=(float)sumX/(float)num;
    float averageYf=(float)sumY/(float)num;
    float averageZf=(float)sumZ/(float)num;
   
    average->x=(int16_t)(averageXf+0.5);
    average->y=(int16_t)(averageYf+0.5);
    average->z=(int16_t)(averageZf+0.5);
}

void Pedometer::incrementStep(){
    step++;
    utility_p->ledBlue();
    //if(!(step%50)) evviva(step);
}

/**
 * getter of actual steps number
 * @param void
 * @returns int number of steps
 */
int Pedometer::getStep(){
    return step;
}

/**
 * print on serial peripheral the values of the average acceleration on the 3 axes
 * debug only
 */
void Pedometer::mediaPrint(){
        printf("\nmedia4x: %i\t",average4.x);
        printf("media16x: %i\t",average16.x);
        printf("media4y: %i\t",average4.y);
        printf("media16y: %i\t",average16.y);
        printf("media4z: %i\t",average4.z);
        printf("media16z: %i\t",average16.z);
}

/**
 * print on serial peripheral the acceleration for the x axe
 * debug only
 */
void Pedometer::dataXPrint(){
    printf("x: %i dataX: ",x);
    for(int i=0;i<15;i++){
        printf("%i",data.lastDataX[i]);
    }
    printf("\n");
}

/**
 * print on serial peripheral the acceleration for the y axe
 * debug only
 */
void Pedometer::dataYPrint(){
    printf("y: %i dataY: ",y);
    for(int i=0;i<15;i++){
        printf("%i",data.lastDataY[i]);
    }
    printf("\n");
}

/**
 * print on serial peripheral the acceleration for the z axe
 * debug only
 */
void Pedometer::dataZPrint(){
    printf("z: %i dataZ: ",z);
    for(int i=0;i<15;i++){
        printf("%i",data.lastDataZ[i]);
    }
    printf("\n");
}
