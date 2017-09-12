#ifndef __FILTER_H__
#define __FILTER_H__

/*! \mainpage notitle
 *
 * \section build_test_sec Build and run unit tests
 *
 * In order to build the code you will need g++, make and pthread. To make and run the tests do : 
 *
 *  $> make test
 *
 * There are two tests in the suite, one for the Range flter and one for the Temporal median filter. Both should show 'PASSED' if successful or 'FAILED' on error.
 *
  * \section build_docs_sec Build this documentation
 *
 * If you have Doxygen installed you can rebuild this documentartion with
 *
 *  $> make docs
 *
 * The documentation main page is at docs/html/index.html
 *
 * \section usage_sec Using the filters
 *
 * \subsection rangeFilter : RangeFilter
 *
 *  Example usage :
 *  \snippet filterTest.cpp Range filter usage
 *
 * \subsection temporalFilter : TemporalFilter
 *
 *  Example usage :
 *  \snippet filterTest.cpp Temporal median filter usage
 */


#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

/*!
 *  \brief     Abstract class used as a base class for the range and temporal median filters

 *  \author    Raj Singh (rajvikrams@gmail.com)
 *  \version   0.1
 *  \date      09-11-2017
 
 *  Child classes will have to implement the update() method.
*/
class Filter{
    
    public:
        virtual std::vector<float> update(std::vector<float> &) = 0;  /*! Pure virtual update method */
        void filter() {};

};


#endif
