/* 
 * File:   lis302dl.cpp
 *  \brief     INTRO VELOCE
 *  \details   DETTAGLI
 *  \author    Omar Scotti
 *  \author    Diego Rondelli
 *  \version   1.0
 *  \date      03/01/2014
 */
#include <cstdio>
#include "miosix.h"
#include "lis302dl.h"
#include "spi1.h"
#include "lis302dl_reg.h"
#include "serial.h"//Rimuovere a fine test

using namespace std;
using namespace miosix;
Spi spi;
SerialPort serial2;

Lis302dl::Lis302dl(){}
/*
 * Private function that set the accelerometer registers
 */
void Lis302dl::memsConfig(){
    serial2.test();
    uint8_t val;
    spi.config();
    val = CTRL_REG1_XEN | CTRL_REG1_YEN  | CTRL_REG1_ZEN | CTRL_REG1_FSEN
            | CTRL_REG1_PDEN;
    spi.write(CTRL_REG1, &val, 1);
}
/*
 * 
 */
void  Lis302dl::getMemsData(int16_t* x, int16_t* y, int16_t* z)
{	
	/* Read out all 6 bytes in one shot */
	*x = spi.singleRead(OUT_X);
        *y = spi.singleRead(OUT_Y);
        *z = spi.singleRead(OUT_Z);
}
/*
void setRange(int8_t range)
{
	uint8_t regval;
	assert_param(range == RANGE_2G || range == RANGE_4G || range == RANGE_8G || range == RANGE_16G);
	regval = spiRead(CTRL_REG4, &regval, 1);
	regval &= ~(3 << 4);
	regval |= range;
	spiWrite(CTRL_REG4, &regval, 1);
}
*/
