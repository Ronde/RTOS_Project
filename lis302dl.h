/* 
 * File:   lis302dl.h
 * Author: user
 *
 * Created on 13 gennaio 2014, 14.00
 */
#ifndef LIS302DL_H
#define	LIS302DL_H

class Lis302dl{
public:
    
    Lis302dl();
    
    void memsConfig(void);
    
    void getMemsData(uint* x, uint* y, uint* z);
    
    //void lis3dlSetRange(int8_t range);
};

#endif	/* LIS302DL_H */