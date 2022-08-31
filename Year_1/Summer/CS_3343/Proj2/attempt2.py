import math
import sys
import re

def Haversine(lat1, lon1, lat2, lon2):
    RADIUS = 3958.8 # in miles
    # convert decimal degrees to radians
    lat1, lon1, lat2, lon2 = map(math.radians, [lat1, lon1, lat2, lon2])
    # haversine formula from Prof's youtube video [https://www.youtube.com/watch?v=X]
    a = ( math.sin(lat2-lat1)/2 )**2 + math.cos(lat1)*math.cos(lat2)*( math.sin(lon2-lon1)/2 )**2
    c = 2*math.atan2(math.sqrt(a), math.sqrt(1-a))
    distance = RADIUS * c
    return distance

def OrderStatistic(lst, num):
    # find the index of the numth smallest element in the list
    # this is the same as the numth smallest element in the sorted list
    return sorted(lst, key=lambda x: x[7])[num-1]
    #TO BE FIXED TO THE ACTUAL ALGORITHM


if len(sys.argv) < 2:
    print("Usage: bash project2.sh <input_file>")
    sys.exit(1)



# Hardcoded query file
query_file = "Queries.csv"

store_list = [] # ID, street, city, state, zip, lat, lon, distance

# ignore first line
with open(query_file, 'r') as my_data:
    with open(sys.argv[1], 'r') as store:
        next(store)
        next(my_data)
        for line in my_data:
            tokens = line.split(",")
            my_lat = float(tokens[0])
            my_lon = float(tokens[1])
            num_stores = int(tokens[2])
            # print(my_lat, my_lon, num_stores)
    
        
            for line in store: #line: ID, street, city, state, postcode, lat, lon
                # try:
                tokens = []
                # Some entries have " or ' in the street name, with commas in the street name or city name
                # This should match pairs of quotes and do the necessary steps
                # The ONLY fields to have two similar quotes in them are the street name
                # Deviating more than this will cause the program to crash or unexpected behaviour
                if (re.search("'.*?,.*?'*.?'+", line) != None): # "'.*,.*'"
                    # ' ' in string
                    three = re.split("'.*?,.*?'*.?'+", line)
                    three[0] = three[0].strip()[:-1] # remove last comma
                    match = re.search("'.*?,.*?'*.?'+", three[0])
                    if "," in three[0]: # city name in quotes
                        tokens += three[0].split(",")
                        three[1] = three[1][1:] # remove first quote
                        # tokens += three[0]
                        name = match.group()[1:-1]
                        name = name[:-1] if name[-1] == "," else name # remove last comma in name
                        tokens.append(name)
                        tokens += three[1].strip().split(",")
                        # print(tokens)
                        # quit()  
                    else: # street name in quotes
                        tokens.append(three[0])
                        three[1] = three[1][1:] # remove first quote
                        tokens.append(match.group()[1:-1]) # remove quotes
                        tokens += three[1].strip().split(",")
                    # print(three)
                    # quit()
                elif (re.search('".*?,.*?"*.?"+', line) != None):
                    # " " in string
                    three = re.split('".*?,.*?"*.?"+', line)
                    three[0] = three[0].strip()[:-1] # remove last comma
                    match = re.search('".*?,.*?"*.?"+', line)
                    if "," in three[0]: # city name in quotes
                        tokens += three[0].split(",")
                        three[1] = three[1][1:] # remove first quote
                        # tokens += three[0]
                        name = match.group()[1:-1]
                        name = name[:-1] if name[-1] == "," else name # remove last comma in name
                        tokens.append(name) # remove quotes
                        tokens += three[1].strip().split(",")
                        # print(tokens)
                        # quit()  
                    else: # street name in quotes
                        tokens.append(three[0])
                        three[1] = three[1][1:] # remove first quote
                        tokens.append(match.group()[1:-1]) # remove quotes
                        tokens += three[1].strip().split(",")
                else:
                    tokens = line.split(",")

                tokens[5] = float(tokens[5])
                try:
                    tokens[6] = float(tokens[6])
                    store_lat = tokens[5]
                    store_lon = tokens[6]
                    store_distance = float(Haversine(my_lat, my_lon, store_lat, store_lon))
                except:
                    print(tokens)
                    quit()
                # store_list.append(tokens.append(store_distance))
                tokens.append(store_distance)
                store_list.append(tokens)
                # except:
                #     print(line)
                #     print(tokens)
                #     continue


            last_n = sorted(store_list, key=lambda x: x[7])[:num_stores]
            ## TO BE FIXED TO THE ACTUAL ALGORITHM

            name = sys.argv[1][:sys.argv[1].find("Data.csv")]

            print("The ", num_stores, " closest ", name + "s" if name[-1] != 's' else name, " to (", my_lat, ", ", my_lon, "):", sep="")
            for i in last_n:
                print(name, " #", i[0], ". ", i[1], ", ", i[2], ", ", i[3], ", ", i[4], ". -  ",  round(i[7],2), " miles.", sep="")
            print()
        
    store.close()
my_data.close()
