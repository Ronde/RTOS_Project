/* 
 * File:   Utility.h
 * Author: user
 *
 * Created on 15 gennaio 2014, 23.03
 */

#ifndef UTILITY_H
#define	UTILITY_H

class Utility
{
private:
    static bool instanceFlag;
    static Utility *utility;
    Utility();
    
public:
    static Utility* getInstance();
    void ledBlue();
    void ledRed();
    void ledGreen();
    void test();
    ~Utility()
    {
        instanceFlag = false;
    }
};

#endif	/* UTILITY_H */

