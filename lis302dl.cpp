/* 
 * File:   lis302dl.cpp
 * Author: Omar Scotti
 *
 * Created on 13 gennaio 2014, 14.00
 */
#include "miosix.h"
#include "lis302dl_reg.h"
#include "spi1.h"
#include <stdint.h>

using namespace std;
using namespace miosix;

/*
 * Private function that set the accelerometer registers
 */
void accellerometerConfig(){
    uint val;
    spiConfig();
    CTRL_REG1 |=( CTRL_REG1_XEN | CTRL_REG1_YEN  | CTRL_REG1_ZEN | CTRL_REG1_FSEN
            | CTRL_REG1_PDEN)
    spiWrite(CTRL_REG1, &val, 1);

}
/*
 * 
 */
void  getAccelerometerData(uint* x, uint* y, uint* z)
{	
	/* Read out all 6 bytes in one shot */
	*x = spiSingleRead(OUT_X);
        *y = spiSingleRead(OUT_Y);
        *z = spiSingleRead(OUT_Z);
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
