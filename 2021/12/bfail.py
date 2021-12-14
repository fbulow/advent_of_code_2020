import pdb

def isSmall(x):
    return ('a'<=x[0]) and ('z'>=x[0])

def logVisit(x, visited):
    if isSmall(x):
        visited = visited.copy()
        try:
            visited[x]+=1
        except:
            visited[x]=1
    return visited

def travel(path, visited, adjacent):
    if path[-1]=='end':
        return 1
    elif visited.get(path[-1], 0) > 2:
        return 0
    else:
        ret = 0
        for x in adjacent[path[-1]]:
            ret+=travel(path+[x],
                        logVisit(x, visited),
                        adjacent)
        return ret

def solb(data):
    adjacent = dict()
    for a,b in (x.strip().split('-') for x in data):
        try:
            adjacent[a].add(b)
        except:
            adjacent[a]=set([b])
        try:
            adjacent[b].add(a)
        except:
            adjacent[b]=set([a])

    return travel(['start'], {'start':1}, adjacent)
    
        

slightly_larger_example = ["dc-end",
                           "HN-start",
                           "start-kj",
                           "dc-start",
                           "dc-HN",
                           "LN-dc",
                           "HN-end",
                           "kj-sa",
                           "kj-HN",
                           "kj-dc"]

