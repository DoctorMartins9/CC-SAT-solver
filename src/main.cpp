#include <vector>           // vector utils     |   std::vector , ...
#include <iostream>         // I/O operations   |   std::cout , ...
#include <chrono>           // time keeping     |   std::chrono, ... 

#include "max_heap.hpp"     // Build max heap   |   hp::MaxHeap, ...
#include "min_heap.hpp"     // Build min heap   |   hp::MinHeap, ...

#define DIM 9999            // Number of nodes

int main(){

    // Max Heap ---------------------------------------------------------------------
    std::cout <<  "Double precision heap-sort test (MaxHeap)" << std::endl;

    std::vector<double> heap;
    
    for(uint64_t i = 0; i < DIM ; i++)
        heap.push_back( static_cast<double>(i) ); 

    auto start = std::chrono::system_clock::now();
    
    hp::MaxHeap<double>::heapSort(heap);
    
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = end - start;

    std::cout << "Number of elements: " << DIM << std::endl;
    std::cout << "Time elapsed: " << diff.count() << " seconds" << std::endl;


    return 0;
}