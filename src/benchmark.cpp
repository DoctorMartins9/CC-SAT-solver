#include <vector>           // vector utils     |   std::vector , ...
#include <iostream>         // I/O operations   |   std::cout , ...
#include <chrono>           // time keeping     |   std::chrono, ... 
#include <cassert>
#include <chrono>
#include <algorithm>
#include <fstream>
#define BENCHMARK
#define EU1
#define F_LIST
#include "sat.hpp"     // Build formula     |   ccsat::Formula, ...

int main(int argc, char **argv){
    
    // Import string
    std::string mode;
    std::string str;
    if(argc == 4){
        mode = argv[1];
        int i = 0;
        std::string input;
        std::ifstream file(argv[2]);
        while(file.good()){
            std::getline(file,input);
            if(std::to_string(i) == argv[3])
                str = input;
            i++;
        }
    }
    else{
        std::cout << "I/O Error: Wrong arguments" << std::endl;
        return 0;
    }
    // Print number of formulas involved
    std::cout << "Number of formulas:" << std::count(str.begin(), str.end(), '|') + 1 << std::endl;
    // Print number of formulas involved
    std::cout << "#Clauses:" << std::count(str.begin(), str.end(), '=') << std::endl;
    // Record the time elapsed to solve
    auto start_time = std::chrono::system_clock::now();
    bool res = ccsat::SOLVE(str,mode);
    auto end_time= std::chrono::system_clock::now();

    // Print the results
    std::chrono::duration<double> diff = end_time - start_time;
    std::cout << "Elapsed: " << diff.count() << " s" << std::endl; // in seconds    
    std::cout << "Result: " << res << std::endl; // in seconds    
    
    return 0;
}
