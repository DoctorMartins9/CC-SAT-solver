#Congruence Closure parallel SAT-Solver 
High performance parallel implementation of a satisfability solver for the congruence closure, able to solve a set of literals in the quantifiers free fragment of first order logic, based on the union of the equality theory, list theory and array theory.

###### Author
*Enrico Martini, VR445202 , Automatic Reasoning Course Project*
<br>
@github/DoctorMartins9

### Usage example
```
#include "sat.hpp"

std::string formula;

// Run CC-Closure procedure
bool is_sat = ccsat::SOLVE(formula,"S");
```

### Run the example (Release mode)
For running an example, in build directory type:

```
cmake ..
make release
../bin/ccsat
```
At this point you can insert the formula and see how the algorithm works. An example of formula accepted is:
```
f(x)!=f(y)&x=y
```
Example of not allowed formulas:
```
(a)=b   ->  a=b             : useless parenthesis are not allowed 
a = b   ->  a=b             : space between literals are not allowed
F&(G|H) ->  (F&G)|(F&H)     : CNF form is not allowed, only DNF
```
### Testing
More than 30 test was done to check the correctness and the strength of the algorithm, including axioms. For real-time test, in build directory type:
```
cmake ..
make -j
./test
```
### Benchmarks
In build directory type:
```
cmake ..
make release
cd ../bin
./benchmark *mode* *path* *number*
```
Where *mode* is parallel ('P') or sequential ('S'), *path* is the path of the file .txt where the clauses are placed and *number* is the number of the line. For running example of the benchmark in bin directory type:
```
./benchmark S ../utils/benchmarks_formula_unsat.txt 10
./benchmark S ../utils/benchmarks_formula_sat.txt 10
```
### Lisp parser
For benchmarking needs, in utils directory there is a python script called lisp_parser.py that allows you to translate SMT-LIB formulas from lisp language to DNF formulas that are legal input of the SAT solver.

### Documentation
LaTex documentation pre-compiled can be found in doc directory.

### Complexity informations
Using [lizard](https://pypi.org/project/lizard/) library for complexity informations, in build directory type:
```
cmake ..
make cyclo
```
