##get first file argument
import sys
file_name = sys.argv[1]

# load file into list
prices = []
with open(file_name) as f:
    for line in f:
        prices.append(float(line))

# prices = [1000000-i for i in range(1000000)]
# print(prices)
# quit()

work = 0
def recurs_profit(lst): #returns (max_profit, min, max)
    global work
    work += 1
    if len(lst) <= 1:
        return (0, lst[0], lst[0])
    elif len(lst) == 2:
        return (lst[1] - lst[0], min(lst[0], lst[1]), max(lst[0], lst[1]))
    else:
        left_profit, left_min, left_max = recurs_profit(lst[:len(lst)//2])
        right_profit, right_min, right_max = recurs_profit(lst[len(lst)//2:])
        max_profit = max(left_profit, right_profit, right_max - left_min)
        return (max_profit, min(left_min, right_min), max(left_max, right_max))



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


max_p = recurs_profit(prices)[0]

import math
print("O(nlog(n)): O(", int(len(prices) * math.log2(len(prices))), ")", sep="")
print("O(n): O(", len(prices), ")", sep="")
print("Our runtime is: O(", work, ")", sep="")

print("Our answer " + str(max_p))