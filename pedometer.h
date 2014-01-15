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
class Pedometer
{
public:
    
   Pedometer();
    
   int start();
   
   void getStep();
   
private:
   
   void stepCounter();
   
   void takeAverage();
   
   void average(Average* average,int num);
   
   void incrementStep();
   
   void ledBlue();
   
   void ledRed(); 
};

#endif	/* PEDOMETER_H */

