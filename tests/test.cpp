#include "max_heap.hpp"
#include "min_heap.hpp"

# define CATCH_CONFIG_MAIN
# include "catch.hpp"
#undef CATCH_CONFIG_MAIN


bool areFloatEqual(float a, float b) {
    const float epsilon = 0.00001f;
    
    if (a == b) 
        return true;
    
    if (std::isnan(a) || std::isnan(b)) 
        return false;

    float abs_a = std::abs(a);
    float abs_b = std::abs(b);
    float diff  = std::abs(a - b);
    
    return (diff / std::max(abs_a, abs_b)) < epsilon;
}

template<typename T>
bool isIncreasing ( std::vector<T>& vec){    
    for(uint64_t i = 1 ; i < vec.size() ; i++)
        if(vec[i-1] > vec[i] )
            return false;  
    return true;
}

template<typename T>
bool isPresent(hp::Heap<T>& heap, T value){
    for(uint64_t i = 0; i < heap.size() ; i++){
        if(heap[i] == value)
            return true;
        else if(std::is_floating_point<T>::value)
            return areFloatEqual(heap[i],value);
    }

    return false;
}

template<typename T>
bool isMinRoot(hp::Heap<T>& heap){
    T root = heap[0];
    for(uint64_t i = 1; i < heap.size() ; i++)
        if(heap[i] < root)
            return false;
    return true; 
}

template<typename T>
bool isMaxRoot(hp::Heap<T>& heap){
    T root = heap[0];
    for(uint64_t i = 1; i < heap.size() ; i++)
        if(heap[i] > root)
            return false;
    return true; 
}


TEST_CASE("Integer Heap Test" , "[IntHeapMax]"){
    
    using T = int;
    
    std::vector<T> vec = {2, 4 , 234, 54,23, 3423, 324 , 34, 32,3};
    const int SIZE = vec.size();

    // Sorting 
    hp::MaxHeap<T>::heapSort(vec);
    REQUIRE( vec.size() == SIZE  );
    REQUIRE( isIncreasing(vec) );

    // Constructor
    hp::MaxHeap<T> heap = hp::MaxHeap<T>(vec);
    REQUIRE(heap.size() == vec.size() );

    // Add element
    heap.addElement(4);
    REQUIRE(heap.size() == SIZE + 1 );
    REQUIRE( isMaxRoot(heap) );
    
    // Erase element by index
    heap.erase(0);
    REQUIRE(heap.size() == SIZE);
    REQUIRE( isMaxRoot(heap) );

    // Add a vector to heap
    std::vector<T> new_vec  = {3,4,24,54,657,32,654,462,6835};
    heap.addVector(new_vec);
    REQUIRE(heap.size() == SIZE + new_vec.size() );
    REQUIRE( isMaxRoot(heap) );

    // Erase element by value    
    heap.eraseByValue(5);
    REQUIRE(!isPresent(heap, 5));
    REQUIRE( isMaxRoot(heap) );

}

TEST_CASE("Float Heap Test (MaxHeap)" , "[FloatHeapTestMax]"){
    
    using T = float;
    
    std::vector<T> vec = {2.0, 4.0 , 234.0, 54.0, 23.0, 3423.0, 324.0, 34.0, 32.0,3.0};
    const int SIZE = vec.size();

    // Sorting 
    hp::MaxHeap<T>::heapSort(vec);
    REQUIRE( vec.size() == SIZE  );
    REQUIRE( isIncreasing(vec) );

    // Constructor
    hp::MaxHeap<T> heap = hp::MaxHeap<T>(vec);
    REQUIRE(heap.size() == vec.size() );

    // Add element
    heap.addElement(4.0);
    REQUIRE(heap.size() == SIZE + 1 );
    REQUIRE( isMaxRoot(heap) );
    
    // Erase element by index
    heap.erase(0);
    REQUIRE(heap.size() == SIZE);
    REQUIRE( isMaxRoot(heap) );

    // Add a vector to heap
    std::vector<T> new_vec  = {3,4,24,54,657,32,654,462,6835};
    heap.addVector(new_vec);
    REQUIRE(heap.size() == SIZE + new_vec.size() );
    REQUIRE( isMaxRoot(heap) );

    // Erase element by value    
    heap.eraseByValue(5.0f);
    REQUIRE(!isPresent(heap, 5.0f));
    REQUIRE( isMaxRoot(heap) );

}

TEST_CASE("Double Heap Test (MaxHeap)" , "[DoubleHeapTestMax]"){
    
    using T = double;
    std::vector<T> vec = {2.0, 4.0 , 234.0, 54.0, 23.0, 3423.0, 324.0, 34.0, 32.0,3.0};
    const int SIZE = vec.size();

    // Sorting 
    hp::MaxHeap<T>::heapSort(vec);
    REQUIRE( vec.size() == SIZE  );
    REQUIRE( isIncreasing(vec) );

    // Constructor
    hp::MaxHeap<T> heap = hp::MaxHeap<T>(vec);
    REQUIRE(heap.size() == vec.size() );

    // Add element
    heap.addElement(4.0);
    REQUIRE(heap.size() == SIZE + 1 );
    REQUIRE( isMaxRoot(heap) );
    
    // Erase element by index
    heap.erase(0);
    REQUIRE(heap.size() == SIZE);
    REQUIRE( isMaxRoot(heap) );

    // Add a vector to heap
    std::vector<T> new_vec  = {3,4,24,54,657,32,654,462,6835};
    heap.addVector(new_vec);
    REQUIRE(heap.size() == SIZE + new_vec.size() );
    REQUIRE( isMaxRoot(heap) );

    // Erase element by value    
    heap.eraseByValue(5.0);
    REQUIRE(!isPresent(heap, 5.0));
    REQUIRE( isMaxRoot(heap) );
}



TEST_CASE("Integer Heap Test (MinHeap)" , "[IntHeapTestMin]"){
  
    using T = int;
    
    std::vector<T> vec = {2, 4 , 234, 54,23, 3423, 324 , 34, 32,3};

    const int SIZE = vec.size();


    // Constructor
    hp::MinHeap<T> heap = hp::MinHeap<T>(vec);
    REQUIRE( heap.size() == SIZE );

    // Add element
    heap.addElement(4);
    REQUIRE(heap.size() == SIZE + 1 );
    REQUIRE( isMinRoot(heap) );
    
    // Erase element by index
    heap.erase(0);
    REQUIRE(heap.size() == SIZE);
    REQUIRE( isMinRoot(heap) );

    // Add a vector to heap
    std::vector<T> new_vec  = {3,4,24,54,657,32,654,462,6835};
    heap.addVector(new_vec);
    REQUIRE(heap.size() == SIZE + new_vec.size() );
    REQUIRE( isMinRoot(heap) );

    // Erase element by value    
    heap.eraseByValue(5);
    REQUIRE(!isPresent(heap, 5));
    REQUIRE( isMinRoot(heap) );

}
