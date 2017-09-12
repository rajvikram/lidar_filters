
/*! Boost unit tests for checking the validity of filter classes */

#include "rangeFilter.hpp"
#include "temporalFilter.hpp"
#define BOOST_TEST_MODULE RangeFilterTest
#include <boost/test/unit_test.hpp>

// Utility method to copy an array in to a vector
void initFloatVector(float *f_arr, int size, std::vector<float> &vec) {
    vec.clear();
    
    for (int i = 0; i< size; i++) {
        vec.push_back(f_arr[i]);
    }
}

BOOST_AUTO_TEST_CASE( filterTest )
{
    std::vector<float> inVec, outVec;
    
    // Test the range filter first
    RangeFilter rf(0.03, 50.0); // Or using default contructor the min and max are assumed
    
    int inArr0[] = {-10.0, 0.029, 0.03, 10.0, 20.0, 30.0, 40.0, 50.0, 50.1, 60.0};
    int outArr0[] = {0.03, 0.03, 0.03, 10.0, 20.0, 30.0, 40.0, 50.0, 50.0, 50.0}; // array with clamped values
    
    initFloatVector(inArr0, 10, inVec);
    initFloatVector(outArr0, 10, outVec);
    
    BOOST_CHECK_EQUAL( rf(inVec), outVec );
    
    
    
}

