"""
Author: Julianus
Assignment 5, Python Lock, CS 3424
"""

import sys
import re

if len(sys.argv) <2:
    print("Need to give some patterns of the form XYZ-R-W")
    sys.exit(1)

clues = sys.argv[1:]
for pattern in clues:
    if re.match('[0-9]{3}-[0-3]-[0-3]', pattern) == None:
        print("Invalid arguement: " + pattern)
        sys.exit(1)

print("Trying ", end="")
# map(lambda x: print(x, end=" "), clues)
[print(x, end=" ") for x in clues]
print("")

possibilities = [ i for i in range(10**3) ]
possibilities = list(map(lambda x: "0"*(3-len(str(x))) + str(x), possibilities))
# print(possibilities)
solutions = []
for possibility in possibilities:
    yes = True
    for clue in clues:
        # check if the clue is satisfied
        # if possibility == "555":
        #     print(clue)
        # if not, break
        # correct = "FFF"
        tokens = clue.split("-")
        xyz = tokens[0]
        r = int(tokens[1])
        w = int(tokens[2])
        for i in range(3):
            if xyz[i] == possibility[i]:
                r -= 1
                # correct = correct[:i] + "F" + correct[i+1:]
            # elif xyz[i] in possibility: # Either one works
            elif possibility[i] in xyz: # Either one works
                w -= 1
                # correct = correct[:i] + "F" + correct[i+1:]
        if r != 0:
            yes = False
            break
        if w != 0:
            yes = False
            break
    if yes:
        solutions.append(possibility)

if len(solutions) == 0:
    print("No Solutions Found")
else:
    for i in range(len(solutions)):
        print("*** Solution #", i+1, " is ", solutions[i], sep="")
print()