#include <vector>           // vector utils     |   std::vector , ...
#include <iostream>         // I/O operations   |   std::cout , ...
#include <chrono>           // time keeping     |   std::chrono, ... 
#include <cassert>
#include <chrono>
#include <algorithm>
// Define the behaviour of the program
#define TEST

#include "sat.hpp"     // Build formula     |   ccsat::Formula, ...

int main(){

    // TEST STRING
    // Equality theory string -----------------------------------------------------------
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
    assert(!ccsat::solve("f(f(f(a)))=f(f(a))&f(f(f(f(a))))=a&f(a)!=a"));
    assert(ccsat::solve("f(x,y)=f(y,x)&f(a,y)!=f(y,a)"));
    assert(!ccsat::solve("f(g(x))=g(f(x))&f(g(f(y)))=x&f(y)=x&g(f(x))!=x"));
    // Z3 Benchmark (https://clc-gitlab.cs.uiowa.edu:2443/SMT-LIB-benchmarks/QF_UF/tree/master/TypeSafe)
    assert(!ccsat::solve("f1!=f2&f3(f4,f5,f6,f7,f8(f9))!=f1&f3(f4,f5,f6,f7,f10)=f1&f10=f8(f9)&f10=f8(f9)&f3(f4,f5,f6,f7,f10)=f1"));
    assert(!ccsat::solve("f1!=f2&f3(f4,f5,f6,f7,f8(f9))!=f1&f3(f4,f5,f6,f7,f10)=f1&f10=f8(f9)&f3(f4,f5,f6,f7,f10)=f1"));
    assert(!ccsat::solve("f1!=f2&f3(f4,f5,f6,f7,f8(f9))!=f1&f3(f4,f5,f6,f7,f10)=f1&f10=f8(f9)"));    
    // List theory strings --------------------------------------------------------------
    // Reflexivity
    assert(!ccsat::solve("x1=x2&y1=y2&cons(x1,y1)!=cons(x2,y2)"));
    // Simmetry
    assert(!ccsat::solve("x=y&car(x)!=car(y)"));
    assert(!ccsat::solve("x=y&cdr(x)!=cdr(y)"));
    // Left projection
    assert(!ccsat::solve("car(cons(x,y))!=x"));
    // Right projection
    assert(!ccsat::solve("cdr(cons(x,y))!=y"));
    // Atom
    assert(ccsat::solve("!atom(cons(x,y))"));
    assert(!ccsat::solve("atom(cons(x,y))"));
    // Construction
    assert(!ccsat::solve("atom(x)&cons(car(x),cdr(x))=x"));
    assert(ccsat::solve("!atom(x)&cons(car(x),cdr(x))=x"));
    // Bradley Manna example
    assert(!ccsat::solve("car(x)=car(y)&cdr(x)=cdr(y)&f(x)!=f(y)&!atom(x)&!atom(y)"));
    assert(ccsat::solve("car(x)=y&cdr(x)=z&x!=cons(y,z)"));
    // Intermediate exam question
    assert(!ccsat::solve("f(b)=b&f(f(b))!=car(cdr(cons(f(b),cons(b,d))))"));
    // Array theory strings -------------------------------------------------------------
    assert(!ccsat::solve("i=k&select(store(x,i,v),k)!=v"));
    assert(!ccsat::solve("i!=k&select(store(x,i,v),k)!=select(x,k)"));
    // Extensionality
    assert(!ccsat::solve("x=y&select(x,z)!=select(y,z)"));
    // Calce example
    assert(!ccsat::solve("i1=j&i1!=i2&select(a,j)=v1&select(store(store(a,i1,v1),i2,v2),j)!=select(a,j)"));
    // Intermediate exam question
    assert(ccsat::solve("e=select(store(a,i,e),j)&select(a,j)!=e"));

    // If core dump is not created
    std::cout << "All test passed!" << std::endl;

    return 0;
}
