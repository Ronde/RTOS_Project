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
    
    uint16_t reciveData();
    
    void csOn();
    
    void csOff();
    
    uint16_t isBusy(int reg);
    
    void sendData(uint8_t data);
    
    int16_t singleRead(uint8_t addr);
    
    int write(uint8_t addr, uint8_t* buffer, uint16_t len);
};
#endif	/* SPI1_H */

