#!/bin/bash


# Student Transcript for XXX XXX, [FIND], @[FIND]
sed -ri 's/, [a-z]{3}[0-9]{3}, @[0-9]{8}$/, XYZ000, @XXXXXXXX/' $1 #> $1 #would be more dynamic with [0-9]+ for detecting and censoring banner ID even if malformed
sed -ri 's/ [A-D|F][+|-]?$/ X/I' $1 #> $1
sed -ri 's/ [0-4][.][0-9]{1,3}$/ X.X/' $1 #> $1
sed -i '/^X/d' $1 #> $1
sed -i '$d' $1 #> $1 #remove last line because the reduced version from the pdf only has 9 lines
# head -n -1 $1 | cat > $1