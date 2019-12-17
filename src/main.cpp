#include <vector>           // vector utils     |   std::vector , ...
#include <iostream>         // I/O operations   |   std::cout , ...
#include <chrono>           // time keeping     |   std::chrono, ... 
#include <cassert>

#define DEBUG
//#define PARSER

#include "sat.hpp"     // Build formula     |   ccsat::Formula, ...

int main(){

    // TEST STRING
    #ifndef DEBUG

    // Equality theory string
    assert(!ccsat::solve("a=b&a!=b"));
    assert(ccsat::solve("a=b&c!=b"));
    // function with one argument
    assert(!ccsat::solve("f(a)=b&f(a)!=b"));
    assert(ccsat::solve("f(a)=b&f(a)!=c"));
    assert(!ccsat::solve("f(f(a))=f(b)&f(f(a))!=f(b)"));
    assert(ccsat::solve("f(f(a))=f(b)&f(f(a))!=c"));
    // function with multiple argument
    assert(!ccsat::solve("f(a,b)=b&f(a,b)!=b"));
    assert(ccsat::solve("f(a,b)=b&f(a,b)!=c"));
    // Bradley-Manna strings
    assert(ccsat::solve("f(x)=f(y)&x!=y"));
    assert(!ccsat::solve("x=y&f(x)!=f(y)"));
    assert(!ccsat::solve("f(a,b)=a&f(f(a,b),b)!=a"));
    assert(!ccsat::solve("f(f(f(a)))=a&f(f(f(f(f(a)))))=a&f(a)!=a"));
    
    // List theory strings
    assert(!ccsat::solve("x1=x2&y1=y2&cons(x1,y1)!=cons(x2,y2)"));
    assert(!ccsat::solve("x=y&car(x)!=car(y)"));
    assert(!ccsat::solve("x=y&cdr(x)!=cdr(y)"));

    // Bradley Manna example
    assert(!ccsat::solve("car(x)=car(y)&cdr(x)=cdr(y)&f(x)!=f(y)&!atom(x)&!atom(y)"));
    // Calce example
    
    // Intermediate exam question
    assert(!ccsat::solve("f(b)=b&f(f(b))!=car(cdr(cons(f(b),cons(b,d))))"));


    // If core dump is not created
    std::cout << "All test passed!" << std::endl;
    #endif

    # ifdef DEBUG
    
    #ifdef PARSER
    //std::string str = "car(cdr(cons(f(b),cons(b,d))))=b";
    //std::string str = "f(g(x),h(y))=c";
    //std::cout << "string to parse: " << str << std::endl;
    //ccsat::Sat s = ccsat::Sat(str);
    #endif
    
    //std::string str = "f(b)=b&f(f(b))!=car(cdr(cons(f(b),cons(b,d))))";
    //std::string str = "car(x)=car(y)&cdr(x)=cdr(y)&f(x)!=f(y)&!atom(x)&!atom(y)";

    std::string str = "f(b)=b&f(f(b))!=car(cdr(cons(f(b),cons(b,d))))";

    //ccsat::Sat s = ccsat::Sat(str);



    bool is_sat = ccsat::solve(str);

    if(is_sat)
        std::cout << "SAT" << std::endl;
    else
        std::cout << "UNSAT" << std::endl;        
    
    # endif

    return 0;
}
