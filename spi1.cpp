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
#include "spi1_reg.h"
#include "address_b.h"
#include "utility.h"
#include "stm32f4xx.h"

#define ALTERNATE_FUNCTION_SPI1 5

using namespace std;
using namespace miosix;

typedef Gpio<GPIOA_BASE, 5> SCK;
typedef Gpio<GPIOA_BASE, 6> MISO;
typedef Gpio<GPIOA_BASE, 7> MOSI;
typedef Gpio<GPIOE_BASE, 3> CS;
SPI_TypeDef* spi_typedef_pun;
Utility* utility_s;

Spi::Spi(){
    utility_s=Utility::getInstance();
}
/**
 * This function sets up all the GPIO used for the accelerometer.
 */
void Spi::config()
{
    utility_s->test();
    
    /* Enable the SPI periph */
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    
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
    
    //QUI MANCA IL DRIVER DEL SPI!!!!!
    
    /* Configure GPIO PIN for Lis Chip select */
    CS::mode(Mode::OUTPUT);
    CS::alternateFunction(ALTERNATE_FUNCTION_SPI1);
    SCK::speed(Speed::_50MHz);
    
    csOff();
    
    spi_typedef_pun=SPI2;
}

uint16_t Spi::reciveData(){
    
      return spi_typedef_pun->DR;
}

void Spi::csOn(){
    //spi_typedef_pun->CR1 |= SSM | SPE;
    CS::low();
}

void Spi::csOff(){
    //spi_typedef_pun->CR1 &= !(SSM | SPE);
    CS::high();
}

uint16_t Spi::isBusy(int reg){
    
    return spi_typedef_pun->SR >> reg;
    
}

void Spi::sendData(uint16_t addr, uint8_t data){
    
    addr |= data;
    
}

int16_t Spi::singleRead(uint8_t addr){
    
    addr &= !(SPI_READ |SPI_MULTI_OP);
    
    int readed = 0;
    addr |= SPI_READ;
    
    /* Transmission start: pull CS low */
	csOn();
	
	/* Send address */
	while(isBusy(SPI_TXE) == RESET){}
	sendData(spi_typedef_pun->DR, addr);
			
	/* Dummy read to make sure shift register is empty.
	 * Note that TXE=1 just tells the Transmit Buffer is empty
	 * and therefore new data can be put in Data Register, not
	 * that actual data on Shift Register has all been put on wire.
	 */
	while(isBusy(SPI_RXNE)){}
	
       reciveData();  

        /* Dummy write */
	while(isBusy(SPI_TXE)){}
	sendData(spi_typedef_pun->DR, 0xff);
	      
	/* Actual read */
	while(isBusy(SPI_RXNE)){}
	readed = reciveData();

	/* Transmission end: pull CS high */
	csOff();

	return readed;
}
   
int Spi::write(uint8_t addr, uint8_t* buffer, uint16_t len){

        addr &= !(SPI_READ |SPI_MULTI_OP);
	
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
	while(isBusy(SPI_BSY)){}
        
	sendData(spi_typedef_pun->DR, addr);
	
	/* Wait data hits slave */ 
	while(isBusy(SPI_RXNE)) {}
        
	reciveData();
		
	/* Send data */
	while(len--){
		while(isBusy(SPI_TXE)){}
                
		sendData(spi_typedef_pun->DR, *buffer++);
			
		while(isBusy(SPI_RXNE));
                
		reciveData();
	}

	/* Transmission end: pull CS high */
	csOff();
	
	return 0;
}