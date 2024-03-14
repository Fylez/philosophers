#!/bin/bash

i=0
j=10
while [ $i -lt 100 ]; do
    cmd="./a.out 5 190 60 60 30| grep eating | wc -l"
    j=$(eval $cmd)
    echo $j
    if [ $j -lt 20 ]; then
        echo "error"
        break
    fi
    i=$[$i+1]
done
if [ $i -lt 100 ]; then
    echo "done"
fi