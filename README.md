#Congruence Closure parallel SAT-Solver 
Text small abstract

###### Author
*Enrico Martini, VR445202 , Automatic Reasoning Course Project*
<br>
@github/DoctorMartins9

### Run the example (Release mode)
For running an example, in build directory type:

```
cmake ..
make release
../bin/ccsat
```

### Usage example
```
#include "sat.hpp"

std::string formula;

// Run CC-Closure procedure
bool isSAT = ccsat::SOLVE(fomrula,"S");

```
### Testing
In build directory type:
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
```
Then in project directory type:
```
bash utils/test_formula.sh *mode* *number*
```
Where *mode* is parallel ('P') or sequential ('S') and *number* is the number of the SMT-LIB QF_UF eq_diamond benchmark, from 1 to 17 is allowed at the moment.
### Documentation
LaTex documentation can be found in doc directory.

### Complexity informations
Using [lizard](https://pypi.org/project/lizard/) library for complexity informations, in build directory type:
```
cmake ..
make cyclo
```
