
/*! Unit tests for checking the validity of filter classes */

#include <iostream>
#include <vector>

#include "rangeFilter.hpp"
#include "temporalFilter.hpp"


// Utility method to copy an array in to a vector
//void initFloatVector(float *f_arr, int size, std::vector<float> &vec) {
//    vec.clear();
//    
//    for (int i = 0; i< size; i++) {
//        vec.push_back(f_arr[i]);
//    }
//}

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

    //! [Range filter usage]
    
    // Create range filter object
    RangeFilter rf(0.03, 50.0); // Or if using default contructor the min and max are assumed
    
    float inArr0[] = {-10.0, 0.029, 0.03, 10.0, 20.0, 30.0, 40.0, 50.0, 50.1, 60.0};
    float outArr0[] = {0.03, 0.03, 0.03, 10.0, 20.0, 30.0, 40.0, 50.0, 50.0, 50.0}; // expected output
    
    std::vector<float> inVec0 (inArr0, inArr0 + sizeof(inArr0) / sizeof(inArr0[0]) );
    std::vector<float> outVec0 (outArr0, outArr0 + sizeof(outArr0) / sizeof(outArr0[0]) );
    
    rf.update(inVec0);
    
    if(!(inVec0 == outVec0)) {
        // Report error for this test and continue
        std::cout << "Range filter returned unexpected output " << std::endl;
        std::cout << "\nExpected array : ";
        printVec(outVec0);
        
        std::cout << "\nReturned array : ";
        printVec(inVec0);
        std::cout << std::endl;
        
        throw(-1);
    }
    //! [Range filter usage]
}


void temporalMedianFilterTest1() {

    //! [Temporal median filter usage]
    // create filter object
    TemporalFilter tf(3); // Depth set to 3
    
    // scanline 1
    float inArr0[] = {0.0, 1.0, 2.0, 1.0, 3.0 };  // input scanline
    float outArr0[] = {0.0, 1.0, 2.0, 1.0, 3.0 }; // expected output
    
    std::vector<float> inVec0 (inArr0, inArr0 + sizeof(inArr0) / sizeof(inArr0[0]) );
    std::vector<float> outVec0 (outArr0, outArr0 + sizeof(outArr0) / sizeof(outArr0[0]) );
    
    tf.update(inVec0);
    
    if(!(inVec0 == outVec0)) {
        std::cout << "\nExpected : "; printVec(outVec0);
        std::cout << "\nReceived : "; printVec(inVec0);
        
        throw(-1);
    }
    
    //! [Temporal median filter usage]
    
    // scanline 2
    float inArr1[] = {1.0, 5.0, 7.0, 1.0, 3.0 };  // input scanline
    float outArr1[] = {0.5, 3.0, 4.5, 1.0, 3.0 }; // expected output
    
    std::vector<float> inVec1 (inArr1, inArr1 + sizeof(inArr1) / sizeof(inArr1[0]) );
    std::vector<float> outVec1 (outArr1, outArr1 + sizeof(outArr1) / sizeof(outArr1[0]) );
    
    tf.update(inVec1);
    
    if(!(inVec1 == outVec1)) {
        std::cout << "\nExpected : "; printVec(outVec1);
        std::cout << "\nReceived : "; printVec(inVec1);
        
        throw(-2);
    }
    
    // scanline 3
    float inArr2[] = {2.0, 3.0, 4.0, 1.0, 0.0 };  // input scanline
    float outArr2[] = {1.0, 3.0, 4.0, 1.0, 3.0 }; // expected output
    
    std::vector<float> inVec2 (inArr2, inArr2 + sizeof(inArr2) / sizeof(inArr2[0]) );
    std::vector<float> outVec2 (outArr2, outArr2 + sizeof(outArr2) / sizeof(outArr2[0]) );
    
    tf.update(inVec2);
    
    if(!(inVec2 == outVec2)) {
        std::cout << "\nExpected : "; printVec(outVec2);
        std::cout << "\nReceived : "; printVec(inVec2);
    
        throw(-3);
    }
    
    // scanline 4
    float inArr3[] = {3.0, 3.0, 3.0, 1.0, 3.0};  // input scanline
    float outArr3[] = {1.5, 3.0, 3.5, 1.0, 3.0 }; // expected output
    
    std::vector<float> inVec3 (inArr3, inArr3 + sizeof(inArr3) / sizeof(inArr3[0]) );
    std::vector<float> outVec3 (outArr3, outArr3 + sizeof(outArr3) / sizeof(outArr3[0]) );
    
    tf.update(inVec3);
    
    if(!(inVec3 == outVec3)) {
        std::cout << "\nExpected : "; printVec(outVec3);
        std::cout << "\nReceived : "; printVec(inVec3);
    
        throw(-4);
    }
    
    // scanline 5
    float inArr4[] = {10.0, 2.0, 4.0, 0.0, 0.0};  // input scanline
    float outArr4[] = {2.5, 3.0, 4.0, 1.0, 1.5}; // expected output
    
    std::vector<float> inVec4 (inArr4, inArr4 + sizeof(inArr4) / sizeof(inArr4[0]) );
    std::vector<float> outVec4 (outArr4, outArr4 + sizeof(outArr4) / sizeof(outArr4[0]) );
    
    tf.update(inVec4);
    
    if(!(inVec4 == outVec4)) {
        std::cout << "\nExpected : "; printVec(outVec4);
        std::cout << "\nReceived : "; printVec(inVec4);
    
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



