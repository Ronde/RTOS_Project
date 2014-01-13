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
void lis3dhConfig(void);
int lis3dhGetAcc(int16_t* x, int16_t* y, int16_t* z);
void lis3dhSetRange(int8_t range);


#endif	/* LIS302DL_H */

