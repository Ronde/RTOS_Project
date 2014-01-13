/**
 * 
 * @author Diego Rondelli
 * 
 */



#include <cstdio>
#include "spi1_reg.h"
#include "miosix.h"
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

void spiConfig()
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

void csOn(){
    
    SPI_TypeDef->CR1 |= (SSM | SPE);
    
}

void csOff(){
 
    SPI_TypeDef->CR1 &= (!(SSM) & !(SPE));
    
}

int spiWrite(uint8_t addr, uint8_t* buffer, int len)
{	
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
	while(SPI_GetFlagStatus(SPI2, SPI_FLAG_TXE) == RESET){}
	SPI_SendData(SPI2, addr);
	
	/* Wait data hits slave */ 
	while(SPI_GetFlagStatus(SPI2, SPI_FLAG_RXNE) == RESET);
	SPI_ReceiveData(SPI2);
		
	/* Send data */
	while(len--){
		while(SPI_GetFlagStatus(SPI2, SPI_FLAG_TXE) == RESET){}
		SPI_SendData(SPI2, *buffer++);
			
		while(SPI_GetFlagStatus(SPI2, SPI_FLAG_RXNE) == RESET);
		SPI_ReceiveData(SPI2);
	}

	/* Transmission end: pull CS high */
	csOff();
	
	return 0;
}
