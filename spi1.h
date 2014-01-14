/* 
 * File:   spi1.h
 * Author: user
 *
 * Created on 14 gennaio 2014, 16.28
 */

#ifndef SPI1_H
#define	SPI1_H
void spiConfig();
uint spiReciveData();
void csOn();
void csOff();
int isBusy(int reg);
void spiSendData(uint addr, uint data);
uint spiSingleRead(uint addr);
int spiWrite(uint addr, uint* buffer, int len);
#endif	/* SPI1_H */

