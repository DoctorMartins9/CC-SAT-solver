#include <vector>           // vector utils     |   std::vector , ...
#include <iostream>         // I/O operations   |   std::cout , ...
#include <chrono>           // time keeping     |   std::chrono, ... 

#include "cc.hpp"     // Build formula     |   ccsat::Formula, ...

int main(){

    ccsat::Variable v1 = ccsat::Variable("f(x)");
    ccsat::Variable v2 = ccsat::Variable("f(y)");
    ccsat::Variable v3 = ccsat::Variable("z");
    ccsat::Variable v4 = ccsat::Variable("f(x,y)");

    ccsat::Clause clasue1 = ccsat::Clause(v1,v2,true);
    ccsat::Clause clasue2 = ccsat::Clause(v3,v4,false);

    ccsat::Formula f = ccsat::Formula();

    f.addClause(clasue1);
    f.addClause(clasue2);

    ccsat::CC cc = ccsat::CC(f);

    std::cout << cc.getFormula().getFormula() << std::endl;

    return 0;
}
