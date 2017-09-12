#ifndef __RANGE_FILTER_H__
#define __RANGE_FILTER_H__

#include "filter.hpp"

/*!
 *  \brief Range filter class
 * 
 *  \author    Raj Singh (rajvikrams@gmail.com)
 *  \version   0.1
 *  \date      09-11-2017
 *
 *   Implements an update method that clamps scanline values to min and max specified by the constructor.
 
*/
class RangeFilter: public Filter {

    private:
        float distMin, distMax;

    public:
    
        /*! Default constructor */
        RangeFilter() {
            distMin = 0.03;     /*! distMin defaults to 0.03 */
            distMax = 50.0;     /*! distMax defaults to 50.0 */
        }
    
        /*! Constructor with min and max */
        RangeFilter(float min, float max) : distMin(min), distMax(max)
        {}
    
        /*! Method takes in a scanline vector object and clamps the object's values between min and max. Returns the modified object upon success */
        std::vector<float> update(std::vector<float> &scanLine) {
            
            for (int i=0; i<scanLine.size(); i++) {
                // Clamp values between min and max limits
                if (scanLine[i] < distMin) scanLine[i] = distMin;
                if (scanLine[i] > distMax) scanLine[i] = distMax;
            }
            
            return scanLine;
        }
};



#endif


