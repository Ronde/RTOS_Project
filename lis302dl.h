/* 
 * File:   lis302dl.h
 *  \brief     INTRO VELOCE
 *  \details   DETTAGLI
 *  \author    Omar Scotti
 *  \author    Diego Rondelli
 *  \version   1.0
 *  \date      10/01/2014
 */
#ifndef LIS302DL_H
#define	LIS302DL_H
#include "types.h"

class Lis302dl{
public:
    
    Lis302dl();
    
    void memsConfig(void);
    
    void getMemsData(int16_t* x, int16_t y, int16_t* z);
    
    //void lis3dlSetRange(int8_t range);
};

#endif	/* LIS302DL_H */