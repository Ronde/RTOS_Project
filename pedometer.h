/* 
 * File:   pedometer.h
 *  \brief     INTRO VELOCE
 *  \details   DETTAGLI
 *  \author    Omar Scotti
 *  \author    Diego Rondelli
 *  \version   1.0
 *  \date      10/01/2014
 */

#ifndef PEDOMETER_H
#define	PEDOMETER_H
#include "types.h"
class Pedometer
{
public:
    
   Pedometer();
    
   void start();
   
   int getStep();
   
private:
    
   struct Average
        {
        int16_t x=0;
        int16_t y=0;
        int16_t z=0;
        }average4,average16;
   
   void stepCounter();
   
   void takeAverage();
   
   void average(Average* average,int num);
   
   void incrementStep();
   
   void ledBlue();
   
   void ledRed(); 
};

#endif	/* PEDOMETER_H */

