#include <vector>           // vector utils     |   std::vector , ...
#include <iostream>         // I/O operations   |   std::cout , ...
#include <chrono>           // time keeping     |   std::chrono, ... 
#include <cassert>
#include <chrono>
#include <algorithm>
// Define the behaviour of the program
#define DEBUG
//#define PARSER

#include "sat.hpp"     // Build formula     |   ccsat::Formula, ...

int main(){
    // Input user defined string
    std::string str;
    std::cout << "Type a formula: " << std::endl;
    std::cin >> str;

    // SAT solve
    if(ccsat::SOLVE(str,"S"))
        std::cout << "SAT" << std::endl;
    else
        std::cout << "UNSAT" << std::endl;        
    
    return 0;
}
