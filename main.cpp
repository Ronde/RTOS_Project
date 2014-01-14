/* 
 *  \brief     INTRO VELOCE
 *  \details   DETTAGLI
 *  \author    Omar Scotti
 *  \author    Diego Rondelli
 *  \version   1.0
 *  \date      14/01/2014
 */

#include <cstdio>
#include "miosix.h"
#include "lis302dl.h"

#define LIMIT 120
#define SOUND_FREQUENCY 50

using namespace std;
using namespace miosix;

int step=0;
unsigned Sensitivity = LIMIT, old_Sensitivity = 0;
unsigned Hysteresis = LIMIT/4, old_Hysteresis = 0;
uint x;
uint y;
uint z;

typedef Gpio<GPIOD_BASE,15> blueLed;
typedef Gpio<GPIOD_BASE,14> redLed;
Lis302dl lis302dl;

typedef enum
   {
   onPause = 0,
   onMove  = 1
    } tState ;

tState currentState= onPause;

void incrementStep(){
    step++;
    //if(!(step%50)) evviva(step);
}

int getStep(){
    return step;
}
/*
void writeData(){
    char str[24]="x: "+x+"\ny: "+y+"\nz: "+z"\n";
    serial.write(str);
}
*/
void ledBlue(){
    blueLed::high();
    usleep(100000);
    blueLed::low();
}

void ledRed(){
    redLed::high();
    usleep(100000);
    redLed::low();
}

void stepCounter(){
        
        //Step are considered as linked to fast variation of the acceleration.
        //We first evaluate the variation (dx/dy/dz) by substracting the current
        //values given by the MEMS to an 'older' value, in fact another average value 
        //done with more value (longer time constant).
        //delta_x = average on last 4 value, minus average done on last 16 value
        unsigned dx =  (x>>2) - (x>>4) ; 
        unsigned dy =  (y>>2) - (y>>4) ; 
        unsigned dz =  (z>>2) - (z>>4) ; 
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

int main(int argc, char** argv) {
    
    blueLed::mode(Mode::OUTPUT);
    
    lis302dl.memsConfig();
    
    while(true){
        
        lis302dl.getMemsData(&x,&y,&z);
        //writeData();
        stepCounter();
        ledRed();
        }
}
