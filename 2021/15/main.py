import pdb

def adjacent(coord, board):
    ret = [[coord[0]-1, coord[1]],
           [coord[0]+1, coord[1]],
           [coord[0],   coord[1]-1],
           [coord[0],   coord[1]+1]]

    return [[a,b] for a,b in ret if
            (a>=0)
            and (b>=0)
            and a<len(board)
            and b<len(board[0])]

assert(adjacent([0,0], [[1,1],[1,1]]) == [[1, 0], [0, 1]])            
assert(adjacent([1,1], [[1,1,1],[1,1,1],[1,1,1]]) == [[0, 1], [2, 1], [1, 0], [1, 2]])

#-1 means unvisited
def emptyCost(board):
    ret= [[None for x in range(len(board[0]))] for y in range(len(board))]
    ret[0][0] = [0, 'start']
    return ret

def get(A, ij):
    return A[ij[0]][ij[1]]

def unvisited(cost, coord):
    return get(cost,coord) == None

def getCostValue(cost, coord):
    if None == get(cost, coord):
        return 0
    else:
        return get(cost, coord)[0]

# [ cost, from ] 
def step(a, b, board, cost): #from a to b
    if( unvisited(cost, b)  or                 #never visited or...
        (getCostValue(cost, a) < getCostValue(cost, b)) ): #cheaper
        return [getCostValue(cost, a)+get(board,b), a]
    else:
        return False
    
assert(step([0,0], [0,1], [[10, 20]], [[[3,'a'], None]])    == [23, [0, 0]])
assert(step([0,0], [0,1], [[10, 20]], [[[3,'a'], [1,'a']]]) == False)

def popSmallest(starts, norm = sum):
    return starts.pop(min([v, i] for i,v in enumerate(norm(x) for x in starts))[1])


data = [[1, 10], [2, 2], [20, 0]]
assert([2, 2] ==  popSmallest(data))
assert([[1, 10], [20, 0]] ==  data)
del data    
    

def travel(board, popper = popSmallest, starts = [[0,0]]):
    starts =[[0,0]]
    cost = emptyCost(board)
    while starts:
        a = popper(starts)
        #a = popSmallest(starts)
        for b in adjacent(a, board):
            co = step(a, b, board, cost)
            if co:
                row, col = b
                cost[row][col] = co
                if not b in starts:
                    starts.append(b)
                

    return cost
    
board = [[int(x) for x in q.strip()] for q in 
         ["1163751742",
          "1381373672",
          "2136511328",
          "3694931569",
          "7463417111",
          "1319128137",
          "1359912421",
          "3125421639",
          "1293138521",
          "2311944581"]]

a = travel(board, lambda x: x.pop())
assert( 40 == a[-1][-1][0] )

b = travel(board);

def trace(cost):
    ij = [len(cost)-1, len(cost[0])-1]
    while ij!=[0,0]:
        print(ij)
        ij = get(cost, ij)[1]
    print(ij)
        

#board = [[int(x) for x in q.strip()] for q in open("input").readlines()]
#ret = travel(board)
#print("a: ", ret[-1][-1][0])

update
    

