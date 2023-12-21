

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


def solA(x):
    return iter(addWalls(x)
    
    

    
    

    
    
