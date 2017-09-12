

#ifndef __TEMPORAL_FILTER_H__
#define __TEMPORAL_FILTER_H__

#include "filter.hpp"
#include <string.h>
#include <errno.h>
#include <pthread.h>

struct medianThreadParams {
    int myId;
    int threadPoolCount;
    std::vector< std::vector<float> > *inputScanlines;
    std::vector<float> *outputScanline;
};


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
            
            int D = inputScanlines->size();
            int N = (*inputScanlines)[0].size();
            std::vector<float> tempVector;
            
            //std::cout << " D = " << D << " N = " << N  << " myId = " << scanlineIdx << std::endl;
            
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
    
        TemporalFilter(int d) : D(d) {
            std::cout << std::endl;
            threadPoolCount = std::thread::hardware_concurrency();
            
            std::cout << threadPoolCount << " cores detected. Will run " << threadPoolCount << " threads ..." << std::endl;
        }
    
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
