#include <vector>           // vector utils     |   std::vector , ...
#include <iostream>         // I/O operations   |   std::cout , ...
#include <chrono>           // time keeping     |   std::chrono, ... 

#include "sat.hpp"     // Build formula     |   ccsat::Formula, ...

int main(){

    // Node debug initialization
    std::string fn = "f" ;
    uint64_t id = 0;
    std::vector<uint64_t> args;
    uint64_t find = 5;
    std::vector<uint64_t> ccpar;
    ccsat::Node n = ccsat::Node(fn,id,args,find,ccpar);

    // Clause debug initialization
    ccsat::Clause c = ccsat::Clause(n,n,false);

    // Formula debug initialization
    ccsat::Formula f = ccsat::Formula();
    f.add_clause(c);

    // Sat debugging initializzation
    ccsat::Sat s = ccsat::Sat(f);

    std::cout << n.get_fn() << std::endl;

    return 0;
}
