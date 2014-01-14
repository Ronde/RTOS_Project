/**
 * 
 * @author Diego Rondelli
 * 
 */
#include <cstdio>
#include "miosix.h"
#include "spi1.h"
#include "spi1_reg.h"
#include "address_b.h"

#define ALTERNATE_FUNCTION_SPI1=5

using namespace std;
using namespace miosix;

typedef Gpio<GPIOA_BASE, 5> SCK;
typedef Gpio<GPIOA_BASE, 6> MISO;
typedef Gpio<GPIOA_BASE, 7> MOSI;
typedef Gpio<GPIOE_BASE, 3> CS;


/**
 * This function sets up all the GPIO used for the accelerometer.
 */
void Spi::config()
{

    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    SCK::mode(Mode::ALTERNATE);
    SCK::alternateFunction(ALTERNATE_FUNCTION_SPI1);
    MISO::mode(Mode::ALTERNATE);
    MISO::alternateFunction(ALTERNATE_FUNCTION_SPI1);
    MOSI::mode(Mode::ALTERNATE);
    MOSI::alternateFunction(ALTERNATE_FUNCTION_SPI1);
    CS::mode(Mode::ALTERNATE);
    CS::alternateFunction(ALTERNATE_FUNCTION_SPI1);
   
}

uint Spi::reciveData(){
    
      return SPI_TypeDef->DR;
}

void Spi::csOn(){
    
    SPI_TypeDef->CR1 |= (SSM | SPE);
    
}

void Spi::csOff(){
 
    SPI_TypeDef->CR1 &= (!(SSM) & !(SPE));
    
}

int Spi::isBusy(int reg){
    
    return SPI_TypeDef->SR >> reg;
    
}

void Spi::sendData(uint addr, uint data){
    
    addr |= data;
    
}

uint Spi::singleRead(uint addr){
    
    addr &= (!(SPI_READ) && !(SPI_MULTI_OP));
    
    uint readed = 0;
    addr |= SPI_READ;
    
    /* Transmission start: pull CS low */
	csOn();
	
	/* Send address */
	while(isBusy(SPI_TXE) == RESET){}
	spiSendData(SPI_TypeDef->DR, addr);
			
	/* Dummy read to make sure shift register is empty.
	 * Note that TXE=1 just tells the Transmit Buffer is empty
	 * and therefore new data can be put in Data Register, not
	 * that actual data on Shift Register has all been put on wire.
	 */
	while(isBusy(SPI_RXNE)){}
	
       spiReciveData();  

		/* Dummy write */
		while(isBusy(SPI_TXE)){}
		spiSendData(SPI_TypeDef->DR, 0xff);
	      
		/* Actual read */
		while(isBusy(SPI_RXNE)){}
		readed = spiReciveData();

	/* Transmission end: pull CS high */
	csOff();

	return readed;
}
    

int Spi::write(uint addr, uint* buffer, int len){

        addr &= (!(SPI_READ) && !(SPI_MULTI_OP));
	
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
        
	spiSendData(SPI_TypeDef->DR, addr);
	
	/* Wait data hits slave */ 
	while(isBusy(SPI_RXNE)) {}
        
	spiReciveData(SPI2);
		
	/* Send data */
	while(len--){
		while(isBusy(SPI_TXE)){}
                
		spiSendData(SPI_TypeDef->DR, *buffer++);
			
		while(isBusy(SPI_RXNE));
                
		spiReciveData(SPI2);
	}

	/* Transmission end: pull CS high */
	csOff();
	
	return 0;
}
