#!/bin/bash

#Author: Julianus

#To run this script, type:
#bash clean.sh <file_name>
#It will automatically generate the Clean file in the same directory
#and with the same name, just ending with Clean
#Be careful not to override your existing files

cleanFile=`echo $1 | sed 's/\..*/Clean/'`
ending=`echo $1 | grep -o '\..*$'`
# echo $cleanFile
# echo $ending
cleanFile=$cleanFile$ending
# echo $cleanFile
if [ ! -f $cleanFile ]; then
    touch $cleanFile
fi

sed 's/#/\/\//g' $1 > $cleanFile
sed -i 's/\s*\/\/\s*/\/\/ /g' $cleanFile
sed -i '/^%.*$/d' $cleanFile