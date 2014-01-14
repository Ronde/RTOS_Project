/* 
 * File:   spi1_reg.h
 * Author: user
 *
 * Created on January 13, 2014, 2:15 PM
 */

#ifndef SPI1_REG_H
#define	SPI1_REG_H

#define DFF             1<<11
#define CPOL            1<<1
#define CPHA            1<<0
#define LSB_FIRST       1<<7
#define SSI             1<<8
#define MSTR            1<<2
#define SPE             1<<6
#define SSM             1<<9

#define SPI_RXNE        0
#define SPI_BSY         7
#define SPI_TXE         1

#endif	/* SPI1_REG_H */

