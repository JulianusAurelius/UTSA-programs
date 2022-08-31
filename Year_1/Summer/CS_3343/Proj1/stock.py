"""
This script takes in stock prices (one number per line) and returns the maximum possible profit from buying one day and selling later


The professor said this couldbe done in O(nlogn) time, but I was able to find a solution in O(n) time, and perhaps a recursive solution in O(n) time as well
Due to that, the professor said he would not use this problem in future classes 

"""

##get first file argument
import sys ## imports in order to grab the file given
file_name = sys.argv[1]

# load file into list
prices = []
with open(file_name) as f: #opens file and loads it into a list
    for line in f:
        prices.append(float(line))

if (len(prices) < 2): #if there's 1 or 0 items, there's no profit
    print("Error: must have at least 2 prices")
    exit()

# import math #I used this to show the runtime expected of different runtimes with the current input
# # feel free to comment this out if you don't want to see it. I used this to see it's O(n)
# print("What we expect to see for the different runtimes")
# # print("O(n²): O(", len(prices)**2, ")", sep="")
# print("O(n*log2(n)): O(", int(len(prices) * math.log2(len(prices))), ")", sep="")
# print("O(n): O(", len(prices), ")", sep="")
# # print("#########################")
# print()

work = 0 #I used this as a rough estimate of runtime

#This recursively breaks it up the problem into smaller pieces and then solves them, as a divide and conquer algorithm
#this runs in little more than O(n) time, from what I see
def recurs_profit(lst): #returns (max_profit, min, max)
    global work #make sure we're using the variable already defined
    work += 1 #add to the work counter just once, since we don't use any loops here
    if len(lst) <= 1: #if there's only 1 item, profit is 0, min/max is 0
        return (0, lst[0], lst[0])
    elif len(lst) == 2: #if there's 2 items, profit is the difference, pass back min/max
        return (lst[1] - lst[0], min(lst[0], lst[1]), max(lst[0], lst[1]))
    else:
        #split the list in half, and pass in the two halves to a recursive call
        #we only really care about the minimum from the left side for profit,
        #but the left max does play into knowing the max number if it happens to be on the right
        #side of a higher recursive call
        left_profit, left_min, left_max = recurs_profit(lst[:len(lst)//2])
        #we really only care about the maximum from the right side for profit,
        #but the right min does matter for the reason above for left max
        right_profit, right_min, right_max = recurs_profit(lst[len(lst)//2:])
        #I *do* use the built-in min and max functions here, but these can be replaced with
        #a simply if/else statement, so it doesn't affect the runtime if this is done
        #in a different language
        max_profit = max(left_profit, right_profit, right_max - left_min)
        #I return a single tuple (you can remove that and just return these values natively in python)
        #but I also unpack these values. You can do this in other languages by just assigning the return
        #value to a variable and then unpacking it on different lines. Or you can pass a variable by
        #address in a language like C, then you don't need to worry about unpacking
        return (max_profit, min(left_min, right_min), max(left_max, right_max))

max_profit = recurs_profit(prices)[0]
print("The optimal solution for", file_name, "is", max_profit)
# To see the runtime, uncomment the line below, and also uncomment the line 24-27 for more context about individual problems
# print("Max profit:", max_profit) # ANSWER
# print("Runtime: O(", work, ")", sep="")


## Note for the grader, I've saved my previous code here to show my work. There are 3 methods I orginally attempted


# O(n). My third attempt, but it was not divide and conquer since it did not call itself, but called similar sister functions (or itself)
# I consolidated my code into one function to overcome this failure in meeting the definition, but there is no real change between this
# and the one above. Other than this one being longer, but perhaps a bit easier to understand when read, but again, being almost 3x longer

# def recurs_profit(lst): #returns max profit
#     global work
#     if len(lst) <= 1:
#         work += 1
#         return 0
#     elif len(lst) == 2:
#         work += 1
#         return lst[1] - lst[0]
#     else:
#         work += 1
#         left_profit, left_min, left_max = left_rec(lst[:len(lst)//2])
#         right_profit, right_max, right_min = right_rec(lst[len(lst)//2:])
#         max_profit = max(left_profit, right_profit)
#         max_profit = max(max_profit, right_max - left_min)
#         # print("right max: ", right_max, " left min: ", left_min, " max profit: ", max_profit)
#         return max_profit
# def left_rec(lst): #returns (profit, min, max)
#     global work
#     if len(lst) <= 1:
#         work += 1
#         # print(lst, end="")
#         # print(" return")
#         return (0, lst[0], lst[0])
#     elif len(lst) == 2:
#         work += 1
#         # print(lst, end="")
#         # print(" return with max_p of ", lst[1] - lst[0], ", min of ", min(lst[0], lst[1]), ", max of ", max(lst[0], lst[1]))
#         return (lst[1] - lst[0], min(lst[0], lst[1]), max(lst[0], lst[1]))
#     else:
#         work += 1
#         left_profit, left_min, left_max = left_rec(lst[:len(lst)//2])
#         right_profit, right_max, right_min = right_rec(lst[len(lst)//2:])
#         max_profit = max(left_profit, right_profit)
#         max_profit = max(max_profit, right_max - left_min)
#         # print(lst, end="")
#         # print(" return with max_p of ", max_profit, ", min of ", min(left_min, right_min), ", max of ", max(left_max, right_max))
#         return (max_profit, min(left_min, right_min), max(left_max, right_max))
# def right_rec(lst): #returns (profit, max, min)
#     global work
#     if len(lst) <= 1:
#         work += 1
#         # print(lst, end="")
#         # print(" return")
#         return (0, lst[0], lst[0])
#     elif len(lst) == 2:
#         work += 1
#         # print(lst, end="")
#         # print(" return with max_p of ", lst[1] - lst[0], ", min of ", min(lst[0], lst[1]), ", max of ", max(lst[0], lst[1]))
#         return (lst[1] - lst[0], max(lst[0], lst[1]), min(lst[0], lst[1]))
#     else:
#         work += 1
#         left_profit, left_min, left_max = left_rec(lst[:len(lst)//2])
#         right_profit, right_max, right_min = right_rec(lst[len(lst)//2:])
#         max_profit = max(left_profit, right_profit)
#         max_profit = max(max_profit, right_max - left_min)
#         # print(lst, end="")
#         # print(" return with max_p of ", max_profit, ", min of ", min(left_min, right_min), ", max of ", max(left_max, right_max))
#         return (max_profit, max(left_max, right_max), min(left_min, right_min))






#linear, O(n). 2nd attempt. This is probably preferable to the divide/conquer method, since you don't have the overhead of recursion,
#and, according to my work counter, is only 20-30 extra steps for every 1000 inputs. But that could also be because of me messing up
#the counter, or just for the files that were tested. Plus, in my mind, it's easier to understand. But a bit more analysis of runtime
#and memory complexity would be needed to determine the best method

max_profit = 0
curr_profit = 0
minum = prices[0] # lowest number we've seen #Also, this mean 'to drink' in indonesian, which I am learning (trying)
maxum = 0 #max number we've seen
for i in range(len(prices)):
    # print()
    # print("num:", prices[i])
    # print("maxum:", maxum)
    # print("minum:",minum)
    # print("max_profit:", max_profit)
    # print("Runtime analysis:")
    if i == len(prices) - 1:
        if prices[i] > maxum: #if this is biggest number, save it
            work += 1
            maxum = prices[i]
            curr_profit = maxum - minum #calculate profit
            if curr_profit > max_profit: #if it's the highest we've seen
                work += 1
                max_profit = curr_profit #save it
    elif prices[i+1] <= prices[i]: #if the next number is less than or equal to our current number
            #then it's not worth calculating profit since the next day would be more
        # print("test")
        work += 1
        continue
    else:
        # print("i+1:", prices[i+1])
        if prices[i] < minum: ## COULD TURN THIS RECURSIVE??
            #If this is the lowest number we've seen, save it
                #We also need to reset max, since our current max is now
                #behind us, and we can sell back in time
            # print("ron")
            work += 1
            minum = prices[i]
            maxum = prices[i+1]
        elif prices[i+1] > maxum:
            #I'll be honest, I forgot why I had this if I do
                #a similar thing on line 86, but this might be for the last index?
            # print("zera")
            work += 1
            maxum = prices[i+1]
        curr_profit = maxum - minum
        work += 1
        if curr_profit > max_profit:
            # print("lol")
            work += 1
            max_profit = curr_profit
print("Max profit:", max_profit) # ANSWER
print("Runtime: O(", work, ")", sep="")





## My first attempt, which was not correct

#PSUEDO CODE BRAINSTORM
#loop through prices
    #if next number is less or equal to current number, or at the end, continue
    #if next number is greater than our current number calculate max profit
    #then loop through to keep going through and find max profit when we find a higher number,
        #if we find a lower number than our current one, recursion with the list from then to the end????
# def max_profit(prices):
#     max = 0
#     global work
#     min_num = prices[0]
#     if (len(prices) == 1):
#         work += 1
#         return 0
#     elif (len(prices) == 2):
#         work += 1
#         return prices[1] - prices[0]
#     for i in range(len(prices)):
#         # print(i)
#         # print(prices)
#         if i == len(prices) - 1:
#             work += 1
#             return max
#         elif (prices[i+1] <= prices[i]):
#             work += 1
#             continue
#         max = prices[i+1] - prices[i]
#         for j in range(i+1, len(prices)):
#             work += 1
#             if prices[j] < prices[i]:
#                 tmp = max_profit(prices[j:])
#                 if tmp > max:
#                     max = tmp
#                 continue
#             elif prices[j] > prices[i+1]:
#                 max = prices[j] - prices[i]
#                 break
#     return max

# max_profit(prices)


## á le prochain fois,
## JulianusAurelius
## Happy Hacking