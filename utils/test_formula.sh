#!/bin/bash

FORMULA=$(head -$2 utils/benchmarks_formula.txt | tail -1)
./bin/benchmark $1 $FORMULA