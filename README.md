# SAT-implementation
Text small abstract

###### Author
*Enrico Martini, VR445202 , Automatic Reasoning Course Project*
<br>
@github/DoctorMartins9

## Run the example (Release mode)
For running an example, in build directory type:

```
cmake ..
make release
../bin/my_heap

```


## Usage
```
#include "max_heap.hpp"

std::vector<T> vec;

// Sorting 
hp::MaxHeap<T>::heapSort(vec);
[...]

```

## Testing
Using the [catch2](https://github.com/catchorg/Catch2) library for testing, in build directory type:

```
cmake ..
make heap_test
./heap_test
```

## Documentation
Using [doxigen](http://www.doxygen.nl/), in build directory type:
```
cmake ..
make doc
```
After this, go to doc/html directory and open with browser "index.html". if you have firefox, from build directory you can type:
```
firefox ../doc/html/index.html &
```

## Complexity informations
Using [lizard](https://pypi.org/project/lizard/) library for complexity informations, in build directory type:

```

cmake ..
make cyclo

```
