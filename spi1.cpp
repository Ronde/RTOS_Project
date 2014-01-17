/* 
 * File:   spi1.cpp
 *  \brief     INTRO VELOCE
 *  \details   DETTAGLI
 *  \author    Omar Scotti
 *  \author    Diego Rondelli
 *  \version   1.0
 *  \date      08/01/2014
 */
#include <cstdio>
#include "miosix.h"
#include "spi1.h"
#include "spi1_constant.h"
#include "utility.h"
#include "stm32f4xx.h"

#define ALTERNATE_FUNCTION_SPI1 5
#define SPIg SPI1


using namespace std;
using namespace miosix;

typedef Gpio<GPIOA_BASE, 5> SCK;
typedef Gpio<GPIOA_BASE, 6> MISO;
typedef Gpio<GPIOA_BASE, 7> MOSI;
typedef Gpio<GPIOE_BASE, 3> CS;

Utility* utility_s;

Spi::Spi(){
    utility_s=Utility::getInstance();
}
/**
 * This function sets up all the GPIO used for the accelerometer.
 */
void Spi::config()
{
    
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    //-----------------------------------------------------------------------
    /* SPI SCK MOSI MISO pin configuration */
    SCK::mode(Mode::ALTERNATE);
    SCK::alternateFunction(ALTERNATE_FUNCTION_SPI1);
    SCK::speed(Speed::_50MHz);
    
    MISO::mode(Mode::ALTERNATE);
    MISO::alternateFunction(ALTERNATE_FUNCTION_SPI1);
    SCK::speed(Speed::_50MHz);
    
    MOSI::mode(Mode::ALTERNATE);
    MOSI::alternateFunction(ALTERNATE_FUNCTION_SPI1);
    SCK::speed(Speed::_50MHz);
    
    //-----------------------------------------------------------------------
    
    /*Deinitialize the SPIx peripheral registers*/
    RCC->APB2RSTR |= RCC_APB2ENR_SPI1EN;
    RCC->APB2RSTR &= !(RCC_APB2ENR_SPI1EN);
    
    /* Enable the SPI periph (Guardare enable per settare)*/
    uint16_t tmpreg = 0;
    tmpreg= (uint16_t)SPIg->CR1;
    tmpreg |= (uint16_t)(SPI_Direction | SPI_Mode | SPI_DataSize | SPI_CPOL |  
                  SPI_CPHA | SPI_NSS |  SPI_BaudRatePrescaler | SPI_FirstBit);
    /* Write to SPIx CR1 */
    SPIg->CR1 = tmpreg;

    /* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
    SPIg->I2SCFGR &= (uint16_t)!((uint16_t)SPI_I2SCFGR_I2SMOD);
    /* Write to SPIx CRCPOLY */
    SPIg->CRCPR = SPI_CRCPolynomial;
    
    SPIg->CR1 |= SPI_CR1_SPE;
    //-----------------------------------------------------------------------
    /* Configure GPIO PIN for Lis Chip select */
    CS::mode(Mode::OUTPUT);
    CS::alternateFunction(ALTERNATE_FUNCTION_SPI1);
    SCK::speed(Speed::_50MHz);
    
    csOff();
}

void Spi::csOn(){
    //spi_typedef_pun->CR1 |= SSM | SPE;
    CS::low();
}

void Spi::csOff(){
    //spi_typedef_pun->CR1 &= !(SSM | SPE);
    CS::high();
}

uint16_t Spi::reciveData(){
    
      return SPIg->DR;
}

void Spi::sendData(uint8_t data){
    
    SPIg->DR = data;
    
}

uint16_t Spi::isBusy(int reg){
    
    if((SPIg->SR & (uint16_t)reg) != (uint16_t)RESET){
        return 0;
    }
    return 1;
    
}

int16_t Spi::singleRead(uint8_t addr){
    
        uint8_t readed = 0;
        addr |= SPI_READ;
    
    /* Transmission start: pull CS low */
        csOn();
        
	/* Send address */
        while(isBusy(SPI_SR_TXE)){}
	sendData(addr);
        
        /* Dummy read to make sure shift register is empty.
         * Note that TXE=1 just tells the Transmit Buffer is empty
         * and therefore new data can be put in Data Register, not
         * that actual data on Shift Register has all been put on wire.
         */
        while(isBusy(SPI_SR_RXNE)){}
        reciveData();

        /* Dummy write */
        while(isBusy(SPI_SR_TXE)){}
        sendData((uint8_t)0x00);
              
        /* Actual read */
        while(isBusy(SPI_SR_RXNE)){}
        readed = reciveData();

	/* Transmission end: pull CS high */
	csOff();

	return readed;
}
   
int Spi::write(uint8_t addr, uint8_t* buffer, uint16_t len){
    
	if(len <= 0){
                return -1;
        }
	
	/* set bit 6 of the address for multiple operation */
	if(len > 1){
		addr |= SPI_MULTI_OP;
	}
        
	/* pull CS low to start trasmission */
	csOn();
	/* Send address */
        while(isBusy(SPI_SR_TXE)){}
        sendData(addr);
        
        /* Wait data hits slave */ 
        while(isBusy(SPI_SR_RXNE)) {}
        reciveData();
        
        /* Send data */
        while(len--){
                while(isBusy(SPI_SR_TXE)){}
                
                sendData(*buffer++);
                        
                while(isBusy(SPI_SR_RXNE)){}
                
                reciveData();
        }

        /* Transmission end: pull CS high */
        csOff();
        
        return 0;
}