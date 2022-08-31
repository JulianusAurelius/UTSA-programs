def dyn_search(string, word_dict, ret_list):
    global counter
    if len(string) == 0:
        return True
    for i in range(len(string)):
        # print(string[:i])
        # print(string[i:])
        # if (string[:i] == "lan" or string[:i] == "land"):
        #     print(string[:i])
        if (string[:i+1] in word_dict):
            # print(string[:i+1])
            next_words = dyn_search(string[i+1:], word_dict, ret_list)
            # print(next_words)
            if (next_words == True):
                # return [string[:i+1]]
                # ret_list.append(string[:i+1])
                # return None
            # elif (next_words != False):
                # return [string[:i+1]] + next_words
                ret_list.insert(0, string[:i+1])
                return True
    return False


word = "aliceinwonderland"

# open file and read in words to dictionary
word_dict = {}
with open("aliceInWonderlandDictionary.txt") as f:
    for line in f:
        word_dict[line.strip()] = True

ret = []
print(dyn_search(word, word_dict, ret))
print(ret)