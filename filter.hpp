#ifndef __FILTER_H__
#define __FILTER_H__

#include <iostream>
#include <vector>
#include <thread>

// Abstract class used as a base class for the range and median filter
class Filter{
    
    public:
        virtual std::vector<float> update(std::vector<float> &) = 0;
    
        void filter() {};

};


#endif
