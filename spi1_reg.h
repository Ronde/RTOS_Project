/* 
 * File:   spi1_reg.h
 *  \brief     INTRO VELOCE
 *  \details   DETTAGLI
 *  \author    Omar Scotti
 *  \author    Diego Rondelli
 *  \version   1.0
 *  \date      10/01/2014
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

