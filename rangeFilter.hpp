#ifndef __RANGE_FILTER_H__
#define __RANGE_FILTER_H__

#include "filter.hpp"

class RangeFilter: public Filter {

    private:
        float distMin, distMax;

    public:
    
        RangeFilter() {
            distMin = 0.03;
            distMax = 50.0;
        }
        
        RangeFilter(float min, float max) : distMin(min), distMax(max)
        {}
    
        std::vector<float> update(std::vector<float> scanLine) {
            
            for (int i=0; i<scanLine.size(); i++) {
                // Clamp values between min and max limits
                if (scanLine[i] < distMin) scanLine[i] = distMin;
                if (scanLine[i] > distMax) scanLine[i] = distMax;
            }
            
            return scanLine;
        }
};



#endif


