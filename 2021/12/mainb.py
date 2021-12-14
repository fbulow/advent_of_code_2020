import pdb

data = ["dc-end", #slightly_larger_example
        "HN-start",
        "start-kj",
        "dc-start",
        "dc-HN",
        "LN-dc",
        "HN-end",
        "kj-sa",
        "kj-HN",
        "kj-dc"]

#data=open('input').readlines()

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

def isSmall(x):
    return ('a'<=x[0]) and ('z'>=x[0])

def logVisit(x, visited):
    if isSmall(x):
        return visited.union({x})
    else:
        return visited

CNT=0
def travel(path, visited, goldenTicket):
    if path[-1]=='end':
        CNT+=1
    elif ((path[-1]=='start') and 'start' in visited):
        return

    else:
        for x in adjacent[path[-1]]:
            if ((not (x in visited)) or goldenTicket):
                if(x in visited):
                    goldenTicket=False
                travel(path+[x],
                       logVisit(x, visited),
                       goldenTicket
                       )

travel(['start'], set(['start']), True)

#len(all_paths)<18404
print(CNT)

