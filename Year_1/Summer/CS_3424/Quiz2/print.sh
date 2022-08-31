#!/bin/bash

counter=1
# full_file=$(cat $1)
# echo $full_file
# for line in $full_file
while read -r line
do
    tmp=$(expr $counter % 3)
    # echo $tmp
    # echo $line
    if [ ! $tmp -eq 0 ]
    then
        echo $line
    fi
    let counter=counter+1
done < $1

if [ $counter -gt 16 ]
then
    echo "big"
else
    echo "small"
fi