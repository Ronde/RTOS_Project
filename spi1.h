/* 
 * File:   spi1.h
 *  \brief     INTRO VELOCE
 *  \details   DETTAGLI
 *  \author    Omar Scotti
 *  \author    Diego Rondelli
 *  \version   1.0
 *  \date      10/01/2014
 */

#ifndef SPI1_H
#define	SPI1_H
#include "types.h"
class Spi
{
public:
    
    Spi();
    
    void config();
    
    uint reciveData();
    
    void csOn();
    
    void csOff();
    
    int isBusy(int reg);
    
    void sendData(uint addr, uint data);
    
    uint singleRead(uint addr);
    
    int write(uint addr, uint* buffer, int len);
};
#endif	/* SPI1_H */

