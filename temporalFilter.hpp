

#ifndef __TEMPORAL_FILTER_H__
#define __TEMPORAL_FILTER_H__

#include "filter.hpp"
#include <string.h>
#include <errno.h>
#include <pthread.h>

/*!
 *  \brief Struct passed as arguments to the compute threads for temporal median filter
 *
 *  \author    Raj Singh (rajvikrams@gmail.com)
 *  \version   0.1
 *  \date      09-11-2017
*/
struct medianThreadParams {
    int myId;
    int threadPoolCount;
    std::vector< std::vector<float> > *inputScanlines;
    std::vector<float> *outputScanline;
};


/*!
 *   \brief     Temporal Median filter class
 *   \author    Raj Singh (rajvikrams@gmail.com)
 *   \version   0.1
 *   \date      09-11-2017
 
 *   Implements an update() method that stores a maximumm of last D scanlines internally and returns the median of values over the past scanlines. The class autodetects the cores on the machine and runs one thread per core. It computes the medians across multiple threads. This is obviously useful for large scanlines with a large D. For smaller values the threads introduce an overhead. 
 
  *  \remark    Maybe in future versions multiple threads are run only for large input data and default s to a single thread for smaller scanlines.
 
*/
class TemporalFilter: public Filter {

    private:
        // Store temporal history for the scanLines
        int D; // This is the 'D' described in problem statement
        std::vector< std::vector<float> > history;
        int threadPoolCount;
        std::vector< pthread_t > medianThreads;
    
    
        // Pthread function for computing the median from scanlines
        // This thread is reponsible for computing medians of all modulo(myId) indexes in the input vectors
        static void* computeMedians(void *args) {
            
            // De-contruct the passed args structure to get the parameters
            struct medianThreadParams *params = (struct medianThreadParams *)args;
            int scanlineIdx = params->myId;
            int threadPoolCount = params->threadPoolCount;
            std::vector< std::vector<float> > *inputScanlines = params->inputScanlines;
            std::vector<float> *outputScanline = params->outputScanline;
            
            // Get the D and N from the scanlines passed in. Not checking to make sure all scanlines are the same size.
            int D = inputScanlines->size();
            int N = (*inputScanlines)[0].size();
            std::vector<float> tempVector;
            
            // This thread will compute medians for multiple elements decided by it's thread id and the total number of threads (stride)
            while (scanlineIdx < N) {
                
                float median = 0.0;
                // Collect all the numbers in a temp vector
                tempVector.clear();
                for (int i = 0; i < D; i++) {
                    tempVector.push_back( (*inputScanlines)[i][scanlineIdx] );
                }
                
                // Sort the values
                sort(tempVector.begin(), tempVector.end());
                
                if ( D % 2 == 0) {
                    // For even number of values, it's the mid-point of middle two values
                    median = float((tempVector[int(D/2) - 1] + tempVector[int(D/2)]) / 2);
                }
                else {
                    // For odd number of values, it's easy.
                    median = float(tempVector[int(D/2)]);
                }
                
                // Store in the output vector
                (*outputScanline)[scanlineIdx] = median;
                
                // Stride to the next scanline index
                scanlineIdx += threadPoolCount;
            
            }
            
            // Exit clean
            pthread_exit(0);
        }
        

    public:
    
        /*! Default constructor. Takes in D as input */
        TemporalFilter(int d) : D(d) {
            std::cout << std::endl;
            threadPoolCount = std::thread::hardware_concurrency();
            
            std::cout << threadPoolCount << " cores detected. Will run " << threadPoolCount << " threads ..." << std::endl;
        }
    
        /*! Update method takes in a scanline as a vector. Calculates the median based on the past D scanlines and returns the median values in the inputScanline object. */
        std::vector<float> update(std::vector<float> &inputScanline) {
            
            //std::vector<float> outputScanline(inputScanline.size());
            // Record scanlines for future calculations. Remove the oldest one
            // if we have reached the max history size (D)
            if (history.size() > D)
                history.erase(history.begin());
            
            // make a copy of the scan line for local history object
            std::vector<float> tempVector(inputScanline);
            history.push_back(tempVector);
            
            // Compute the median. Spawn multiple threads to do the work.
            for (int i = 0; i < threadPoolCount; i++) {
                
                // Prepare a struct with the parameters to pass to the thread
                pthread_t tId;
                struct medianThreadParams *params = new medianThreadParams();
                params->myId = i;
                params->threadPoolCount = threadPoolCount;
                params->inputScanlines = &history;
                params->outputScanline = &inputScanline;
                
                if(pthread_create(&tId, NULL, &computeMedians, (void *)params) != 0) {
                    std::cerr << "Could not create pthread successfully : " << strerror(errno) << std::endl;
                    exit(1);
                }
                
                medianThreads.push_back(tId);
            }
            
            // Now wait for all threads to finish
            for (int i = 0; i < threadPoolCount; i++) {
                //std::cout << "Waiting for thread # " << i << "..." << std::flush;
                pthread_join(medianThreads[i], NULL);
                //std::cout << "Done" << std::endl;
            }
            
            return inputScanline;
        }
    
};



#endif
