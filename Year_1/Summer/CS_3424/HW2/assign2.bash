#!/bin/bash

for file in $@
do
    bash assign2.sed $file
done

# echo $#
# Old code I played with to try it out, kept to show work
# for i in {1..$#}
# do
#     # bash assign2.sed $i
#     echo $i
# done