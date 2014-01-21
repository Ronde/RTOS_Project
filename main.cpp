/**
 * File:   lis302dl.cpp
 *  \brief     main class. It only starts the program
 *  \author    Omar Scotti
 *  \author    Diego Rondelli
 *  \version   1.0
 *  \date      14/01/2014
 */

#include <cstdlib>
#include <cstdio>
#include "pedometer.h"
#include "statistics.h"

using namespace std;

Pedometer* pedometer;
Statistics* statistics;

/*
 * Main method, starts the pedometer
 */
int main(int argc, char** argv) {
    pedometer = Pedometer.getInstance();
    std::thread first (pedometer.start());
    std::thread second (statistics = Statistics.getInstance());
    
    first.join();
    second.join();
    
    return 0;
}

