def dyn_search(string, word_dict):
    if len(string) == 0:
        return True
    ret = []
    for i in range(len(string)):
        if (string[:i+1] in word_dict):
            next_words = dyn_search(string[i+1:], word_dict)
            if (next_words == True):
                return ret + [string]
            elif (type(next_words) == list and len(next_words) > 0):
                for list_of_words in next_words:
                    if type(list_of_words) == str:
                        ret.append([string[:i+1], list_of_words])
                    else:
                        ret.append([string[:i+1]] + list_of_words)
    # return False
    return ret

# open file and read in words to dictionary
word_dict = {}
with open("aliceInWonderlandDictionary.txt") as f:
    for line in f:
        word_dict[line.strip()] = True
word = "william"

solutions = dyn_search(word, word_dict)
if len(solutions) == 0:
    print(word, "cannot be split into AiW words.")
else:
    is_single = filter(lambda item: type(item) == str, solutions)
    if len(list(is_single)) > 0:
        print(word, "can be split into one AiW word:")
        for solution in solutions:
            if type(solution) == str:
                print(solution)
            else:
                print(" ".join(solution))
    else:
        least = min(solutions, key=lambda item: len(item))
        print(word, "can be split into", len(least), "AiW words:")
        print(" ".join(least))
        
    # for solution in solutions:
    #     if type(solution) == str:
    #         print(word, "can be split into 1 AiW word:", end=" ")
    #         print(solution, end="")
    #     else:
    #         print(word, "can be split into", len(solution), "AiW words:", end=" ")
    #         for match in solution:
    #             print(" ", match, end="", sep="")
    #     print()