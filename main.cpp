/**
 * File:   lis302dl.cpp
 *  \brief     main class. It only starts the program
 *  \author    Omar Scotti
 *  \author    Diego Rondelli
 *  \version   1.0
 *  \date      14/01/2014
 */

#include <cstdlib>
#include "pedometer.h"
#include "statistics.h"
#include <thread>

Pedometer* pedometer;
Statistics* statistics;

void startPedometer(){
    pedometer.start();
}

void startStatistics(){
    statistics.start();
}

/*
 * Main method, starts the pedometer
 */
int main(int argc, char** argv) {
    
    pedometer = Pedometer.getInstance();
    std::thread first (startPedometer);
    statistics = Statistics.getInstance();
    std::thread second (startStatistics);
    
    first.join();
    second.join();
    
    return 0;
}

