#! /bin/bash

x=0

while [ $x -lt 10000 ]; do
    ./a.out
    ((x++))
done
