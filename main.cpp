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
#include <pthread.h>

Pedometer* pedometerApp;
Statistics* statistics;

void *startPedometer(void *arg){
    pedometerApp->start();
}

void *startStatistics(void *arg){
    statistics->start();
}

/*
 * Main method, starts the pedometer
 */
int main(int argc, char** argv) {
    
    pedometerApp = Pedometer::getInstance();
    
    pthread_t pedometerThread;
    pthread_create(&pedometerThread,NULL,&startPedometer,NULL);
    
    statistics = Statistics::getInstance();
    
    pthread_t statisticsThread;
    pthread_create(&statisticsThread,NULL,&startStatistics,NULL);
    
    pthread_join(pedometerThread,NULL);
    pthread_join(statisticsThread,NULL);
    
    return 0;
}

