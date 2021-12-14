import pdb


adjacent = dict()

for a,b in (x.strip().split('-') for x in open('input').readlines()):
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

all_paths=set()  
def travel(path, all_paths, visited):
    if path[-1]=='end':
        all_paths.add(",".join(path))
    else:
        for x in adjacent[path[-1]]:
            if not x in visited:
                travel(path+[x],
                       all_paths,
                       logVisit(x, visited)
                       )

travel(['start'], all_paths, set(['start']))

len(all_paths)<18404


