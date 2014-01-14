/* 
 * File:   lis302dl.h
 * Author: user
 *
 * Created on 13 gennaio 2014, 14.00
 */

#include<stdint.h>

#ifndef LIS302DL_H
#define	LIS302DL_H

/* Public APIs */
void accelerometerConfig(void);
int getAccellerometerData(uint* x, uint* y, uint* z);
//void lis3dlSetRange(int8_t range);


#endif	/* LIS302DL_H */