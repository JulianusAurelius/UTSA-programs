from numpy import inf # I previously used the math module but for some reason it doesn't have inf on the fox servers

def Bellman_Ford(graph, vertex):
    distance = [inf for i in range(len(graph))]
    distance[vertex] = 0
    for i in range(len(graph)-1):
        for j in range(len(graph)):
            for k in range(len(graph[j])):
                if distance[j] + graph[j][k] < distance[k]:
                    distance[k] = distance[j] + graph[j][k]
    # ## check for negative cycle ## took out after reading we can assume no negative cycle
                                    ## kept to show work
    # for i in range(len(graph)):
    #     for j in range(len(graph[i])):
    #         if distance[i] + graph[i][j] < distance[j]:
    #             return None
    return distance


input_file = "graphInput.txt"
paths_to_look_for_file = "shortestPaths.txt"

with open(input_file, "r") as f:
    num_nodes = int(f.readline())
    graph = [[inf if i!= j else 0 for i in range(num_nodes)] for j in range(num_nodes)]

    # print(graph)
    for line in f:
        # print(line.strip())
        line = line.strip().split(" ")
        graph[int(line[0])][int(line[1])] = int(line[2])
    
    with open(paths_to_look_for_file, "r") as paths:
        for line in paths:
            line = line.strip().split(" ")
            vertex_from = int(line[0])
            vertex_to = int(line[1])
            distances = Bellman_Ford(graph, vertex_from)
            print("A shortest path from {} to {} has length {}.".format(vertex_from, vertex_to, distances[vertex_to]))
        paths.close()
    f.close()
# for i in graph:
#     print(i)