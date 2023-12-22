import sys

def addHorizontalWalls(x):
    N = len(x[0])
    w = [N*"#"]
    return w + x + w

def addVerticalWalls(x):
    return ["#" + a + "#" for a in x]

def addWalls(x):
    return addVerticalWalls(addHorizontalWalls(x))

def newValue(row, col, garden):
    if garden[row][col]=="#" :
        return "#"
    elif isAdjacent(row, col, garden):
        return "O"
    else:
        return "."
    
def isAdjacent(row, col, garden):
    for x,y in ((row-1, col),
                (row+1, col),
                (row,   col-1),
                (row,   col+1)):
        if isGardner(garden[x][y]):
            return True
    return False
        
def isGardner(char):
    return char in ("S", "O")

def iter(N, garden):
    if N==0:
        return garden
    else:
        cpy = [[" "]*len(row) for row in garden]
        for row in range(len(garden)):
            for col in range(len(garden[row])):
                cpy[row][col] = newValue(row, col, garden)
        return iter(N-1, cpy)

def readFile(filename):
    return [x.strip() for x in open(filename).readlines() if not len(x)==0]

def countGardners(garden):
    return sum(sum(isGardner(x) for x in row) for row in garden)


def solA(file):
    return countGardners(iter(64, addWalls(readFile(file))))
    

def genIsRock(rocks, rows, cols):
    def ret(pos):
        return (pos[0]%rows, pos[1]%cols) in rocks
    return ret
    

def adjacent(pos):
    row, col = pos
    return ((row-1, col),
            (row+1, col),
            (row,   col-1),
            (row,   col+1))
    

def isAdjacentB(pos, permanent, current):
    for npos in adjacent(pos):
        if npos in permanent: return True
        elif npos in current: return True
    return False

def iterB(N,
          isRock,
          edge,
          counted,
          retA, retB
          ):
    if N==-1:
        return retA
    else:
        newEdge = set() #new current
        for pos in edge:
            if pos in counted:
                pass
            elif isRock(pos):
                pass
            else:
                retB = retB+1
                for p in adjacent(pos):
                    newEdge.add(p)
    return iterB(N-1,
                 isRock,
                 newEdge,
                 edge.union(counted),
                 retB, retA #retA and retB intentionally swapped
                 )

def solB(file, N = 26501365):
    rocks = set()
    newEdge = set();

    data = readFile(file)
    for row in range(len(data)):
        for col in range(len(data[row])):
            c = data[row][col]
            if c=="#":
                rocks.add((row,col))
            elif c=="S":
                newEdge.add((row,col))
    return iterB(N,
                 genIsRock(rocks, len(data), len(data[0])),
                 newEdge,
                 set(),
                 0,0)
                 

print((solB("example", 6), "16 garden plots."))
print((solB("example", 10 ), "50 garden plots."))
print((solB("example", 50 ), "1594 garden plots."))
print((solB("example", 100), "6536 garden plots."))

    
                
                
    
    

    
    
