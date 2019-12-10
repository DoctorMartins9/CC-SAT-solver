#include <vector>           // vector utils     |   std::vector , ...
#include <iostream>         // I/O operations   |   std::cout , ...
#include <chrono>           // time keeping     |   std::chrono, ... 

#include "variable.hpp"     // Build min heap   |   hp::MinHeap, ...

int main(){

    ccsat::Variable v = ccsat::Variable("f(x)");
    std::cout << v.getValue() << std::endl;
    //ccsat::Clause clasue = new ccsat::Clasue();

    return 0;
}