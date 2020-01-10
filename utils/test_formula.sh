#!/bin/bash

# Clear
rm $2

# Head
echo -e "Test;#Formulas;Sequential;Parallel" 1>> $2

# Tests
for i in {7..15}
do
    echo -n $i 1>> $2
    echo -n ";" 1>> $2
    echo -n $(./benchmark S $1 $i | grep Number  | cut -d':' -f2 | sed 's/\./,/') 1>> $2
    echo -n ";" 1>> $2
    echo -n $(./benchmark S $1 $i | grep Elapsed | cut -d' ' -f2 | sed 's/\./,/') 1>> $2
    echo -n ";" 1>> $2
    ./benchmark P $1 $i | grep Elapsed | cut -d' ' -f2 | sed 's/\./,/' 1>> $2
done

# Print
cat $2

