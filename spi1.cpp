/**
 * 
 * \author Diego Rondelli
 * prova
 */
#include <cstdio>
#include "miosix.h"
#include <unistd.h>

using namespace std;
using namespace miosix;

typedef Gpio<GPIOB_BASE, 5> SCK;
typedef Gpio<GPIOB_BASE, 6> MISO;
typedef Gpio<GPIOB_BASE, 7> MOSI;

/**
 * This function sets up all the GPIO used for the accelerometer.
 */

void spiConfig()
{
    SCK::mode(Mode::ALTERNATE);
    SCK::alternateFunction(0);
    MISO::mode(Mode::ALTERNATE);
    MISO::alternateFunction(0);
    MOSI::mode(Mode::ALTERNATE);
    MOSI::alternateFunction(0);
    //TODO config PE3
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
}


