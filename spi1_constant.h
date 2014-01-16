/* 
 * File:   address_b.h
 * Author: user
 *
 * Created on January 13, 2014, 2:16 PM
 */

#ifndef ADDRESS_B_H
#define	ADDRESS_B_H

#define SPI_MULTI_OP            1<<6
#define SPI_READ                1<<7
#define SPI_Direction           (uint16_t)0x0000
#define SPI_Mode                (uint16_t)0x0104
#define SPI_DataSize            (uint16_t)0x0000
#define SPI_CPOL                (uint16_t)0x0000
#define SPI_CPHA                 (uint16_t)0x0000
#define SPI_NSS                  (uint16_t)0x0200
#define SPI_BaudRatePrescaler   (uint16_t)0x0008
#define SPI_FirstBit             (uint16_t)0x0000
#define SPI_CRCPolynomial       7
#define SPI_NSS                 (uint16_t)0x02007

#endif	/* ADDRESS_B_H */

