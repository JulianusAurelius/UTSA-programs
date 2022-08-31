def dyn_search(curr_string, word_dict): # When given string: [first][second], ie Hello can be [H][ello], or any other combination
    if curr_string == "":
        return "", 0
    elif curr_string in word_dict: # the entire string matches, best case
        return curr_string, 1
    else:
        curr =  None
        best = None
        for i in range(len(curr_string)):
            if curr_string[:len(curr_string)-i] in word_dict: # if [first] is in word_dict
                next_word, count = dyn_search(curr_string[len(curr_string)-i:], word_dict) # pass [second] to dyn_search
                if next_word != None: # if the rest of the string can be split into words in AiW
                    # return curr_string[:len(curr_string)-i] + " " + next_word, count + 1
                    if best == None or count < best: # if the current search we're on is better than ones we've seen
                        best = count # save count
                        curr = curr_string[:len(curr_string)-i] + " " + next_word # save current string
        if curr != None: # if we found a string that can be split into words in AiW
            return curr, best + 1 # we return the best we've seen (by only saving the best in memory from lines 14-16)
        return None, 0 # no solution for this string

# open file and read in words to dictionary
word_dict = {}
with open("aliceInWonderlandDictionary.txt") as f:
    for line in f:
        word_dict[line.strip()] = True

with open("input.txt") as f:
    for line in f:
        word = line.strip()
        solution, count = dyn_search(word, word_dict)
        # print(solutions, count)
        if count == 0:
            print(word, "cannot be split into AiW words.")
        if count == 1:
            print(word, "can be split into 1 AiW word:", solution)
        if count > 1:
            print(word, "can be split into", count, "AiW words:", solution)