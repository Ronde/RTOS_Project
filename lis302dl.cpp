/**
 *\author Omar Scotti
 * 
 */
#include <cstdio>
#include <unistd.h>
#include "miosix.h"
#include "lis302dl_reg.h"
        
using namespace std;
using namespace miosix;
/**
 * Start function that set the communication
 */
public void start(){
    accelerometerConfig();
    
}
/*
 * Private function that set the accelerometer registers
 */
private void accellerometerConfig(){
    CTRL_REG1 |=( CTRL_REG1_XEN | CTRL_REG1_YEN  | CTRL_REG1_ZEN | CTRL_REG1_FSEN
            | CTRL_REG1_PDEN)
}
/*
 * 
 */
private int getAcc(int16_t* x, int16_t* y, int16_t* z)
{
	uint8_t buffer[6];
	
	/* Read out all 6 bytes in one shot */
	spiRead(OUT_X, buffer, 6);
	*x = *((int16_t*)buffer);
	*y = *((int16_t*)(buffer + 2));
	*z = *((int16_t*)(buffer + 4));
	return 0;
}



