
/*! Unit tests for checking the validity of filter classes */

#include <iostream>
#include <vector>

#include "rangeFilter.hpp"
#include "temporalFilter.hpp"


// Utility method to copy an array in to a vector
void initFloatVector(float *f_arr, int size, std::vector<float> &vec) {
    vec.clear();
    
    for (int i = 0; i< size; i++) {
        vec.push_back(f_arr[i]);
    }
}

void printVec(std::vector<float> &vec){
    std::cout << " [ ";
    for (int i = 0; i< vec.size(); i++) {
        std::cout << vec[i];
        
        if(i < (vec.size() - 1))
            std::cout << ", ";
    }
    
    std::cout << " ]" << std::endl;
}

// Test if input array with out of bounds values is clamped within given range.
void rangeFilterTest1() {

    std::vector<float> inVec, outVec;
    
    // Test the range filter first
    RangeFilter rf(0.03, 50.0); // Or using default contructor the min and max are assumed
    
    float inArr0[] = {-10.0, 0.029, 0.03, 10.0, 20.0, 30.0, 40.0, 50.0, 50.1, 60.0};
    float outArr0[] = {0.03, 0.03, 0.03, 10.0, 20.0, 30.0, 40.0, 50.0, 50.0, 50.0}; // expected output
    
    initFloatVector(inArr0, 10, inVec);
    initFloatVector(outArr0, 10, outVec);
    
    rf.update(inVec);
    
    if(!(inVec == outVec)) {
        // Report error for this test and continue
        std::cout << "Range filter returned unexpected output " << std::endl;
        std::cout << "\nExpected array : ";
        printVec(outVec);
        
        std::cout << "\nReturned array : ";
        printVec(inVec);
        std::cout << std::endl;
        
        throw(-1);
    }
    
}


void temporalMedianFilterTest1() {

    std::vector<float> inVec, outVec;
    
    // Test the range filter first
    TemporalFilter tf(3); // Depth set to 3
    
    // scanline 1
    float inArr0[] = {0.0, 1.0, 2.0, 1.0, 3.0 };  // input scanline
    float outArr0[] = {0.0, 1.0, 2.0, 1.0, 3.0 }; // expected output
    
    initFloatVector(inArr0, 5, inVec);
    initFloatVector(outArr0, 5, outVec);
    
    tf.update(inVec);
    
    if(!(inVec == outVec)) {
        std::cout << "\nExpected : "; printVec(outVec);
        std::cout << "\nReceived : "; printVec(inVec);
        
        throw(-1);
    }
    
    // scanline 2
    float inArr1[] = {1.0, 5.0, 7.0, 1.0, 3.0 };  // input scanline
    float outArr1[] = {0.5, 3.0, 4.5, 1.0, 3.0 }; // expected output
    
    initFloatVector(inArr1, 5, inVec);
    initFloatVector(outArr1, 5, outVec);
    
    tf.update(inVec);
    
    if(!(inVec == outVec)) {
        std::cout << "\nExpected : "; printVec(outVec);
        std::cout << "\nReceived : "; printVec(inVec);
        
        throw(-2);
    }
    
    // scanline 3
    float inArr2[] = {2.0, 3.0, 4.0, 1.0, 0.0 };  // input scanline
    float outArr2[] = {1.0, 3.0, 4.0, 1.0, 3.0 }; // expected output
    
    initFloatVector(inArr2, 5, inVec);
    initFloatVector(outArr2, 5, outVec);
    
    tf.update(inVec);
    
    if(!(inVec == outVec)) {
        std::cout << "\nExpected : "; printVec(outVec);
        std::cout << "\nReceived : "; printVec(inVec);
    
        throw(-3);
    }
    
    // scanline 4
    float inArr3[] = {3.0, 3.0, 3.0, 1.0, 3.0};  // input scanline
    float outArr3[] = {1.5, 3.0, 3.5, 1.0, 3.0 }; // expected output
    
    initFloatVector(inArr3, 5, inVec);
    initFloatVector(outArr3, 5, outVec);
    
    tf.update(inVec);
    
    if(!(inVec == outVec)) {
        std::cout << "\nExpected : "; printVec(outVec);
        std::cout << "\nReceived : "; printVec(inVec);
    
        throw(-4);
    }
    
    // scanline 5
    float inArr4[] = {10.0, 2.0, 4.0, 0.0, 0.0};  // input scanline
    float outArr4[] = {2.5, 3.0, 4.0, 1.0, 1.5}; // expected output
    
    initFloatVector(inArr4, 5, inVec);
    initFloatVector(outArr4, 5, outVec);
    
    tf.update(inVec);
    
    if(!(inVec == outVec)) {
        std::cout << "\nExpected : "; printVec(outVec);
        std::cout << "\nReceived : "; printVec(inVec);
    
        throw(-5);
    }
    
}

int main(int argc, char **argv)
{
    try {
        
        std::cout << "\n----------------------------------------------------------\n";
        std::cout << "Testing range filter with out of bound values ...\n" << std::flush;
        rangeFilterTest1();
        std::cout << "PASSED";
        
        std::cout << "\n----------------------------------------------------------\n";
        std::cout << "Testing temporal median filter with 5 input scanlines ..." << std::flush;
        temporalMedianFilterTest1();
        std::cout << "PASSED";
    
    }
    catch (int errcode) {
        std::cout << " FAILED with error code : " << errcode;
        return errcode;
    }
    
    std::cout << std::endl;
    return 0;
    
}



