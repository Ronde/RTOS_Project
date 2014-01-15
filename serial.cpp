
#include "serial.h"
#include "serial_registers.h"

//PA2 : USART2 TX
//PA3 : USART2 RX

static const int bufsize=16;
static char rxbuffer[bufsize];
static int putpos=0;
static int getpos=0;
static volatile int numchar=0;

SerialPort::SerialPort()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	GPIOA->AFR[0] |= (7<<(2*4)) | (7<<(3*4));
	GPIOA->MODER |= (2<<(2*2)) | (2<<(3*2));

	USART2->CR1 = USART_CR1_UE | USART_CR1_RXNEIE;
	USART2->BRR = (52<<4) | (1<<0);
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;

	NVIC->ISER[1]=1<<6;
}

void SerialPort::write(const char *str)
{
	while((*str)!='\0')
	{
		//Wait until the hardware fifo is ready to accept one char
		while((USART2->SR & USART_SR_TXE)==0) ;
		USART2->DR=*str++;
	}
}

void SerialPort::test(){
    char str[24]="Sono passato qui:  \r\n";
    write(str);
}
