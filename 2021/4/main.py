#!/usr/bin/python3
def get_input(lines):
    boards = []
    board = [] 
    for row in lines[2:]:
        if row=='\n':
            boards.append(board)
            board = [] 
        else:
            v = [int(x) for x in row.split()]
            assert(all(x!=-1 for x in v))
            board.append(v)
    if (len(board)!=0):
        boards.append(board)
    return ([int (x) for x in lines[0].split(",")], boards)

def apply(board, number):
    for i, row in enumerate(board):
        for j, v in enumerate(row):
            if v == number:
                board[i][j]=-1
    return board

def score(board):
    return sum(sum(r for r in row if r>-1) for row in board)

def done(board):
    for b in board:
        if all(x==-1 for x in b):
            return True
    else:
        for col in range(5):
            if all(b[col]==-1 for b in board):
                return True
    return False

def solution_a(random_numbers, boards):
    for n in random_numbers:
        for ib, board in enumerate(boards):
            apply(board,n)
            if(done(board)):
                return n*score(board)
            
#random_numbers, boards = example()
def example():
    return get_input(["7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1",
                                   "\n",
                                   "22 13 17 11  0",
                                   " 8  2 23  4 24",
                                   "21  9 14 16  7",
                                   " 6 10  3 18  5",
                                   " 1 12 20 15 19",
                                   "\n",
                                   " 3 15  0  2 22",
                                   " 9 18 13 17  5",
                                   "19  8  7 25 23",
                                   "20 11 10 24  4",
                                   "14 21 16 12  6",
                                   "\n",
                                   "14 21 17 24  4",
                                   "10 16 15  9 19",
                                   "18  8 23 26 20",
                                   "22 11 13  6  5",
                                   " 2  0 12  3  7"])
assert(3==len(example()[1]))
random_numbers, boards = example()
xa=solution_a(random_numbers, boards)
assert(4512 == xa)

       
random_numbers, boards = get_input(open("input").readlines())            
a=solution_a(random_numbers, boards)
       
assert(a!=3987)
assert(a!=4068)
print("a: ", a)
    

def finish(numbers, board):
    count=0
    for n in numbers:
        count+=1
        apply(board, n)
        if(done(board)):
            return [count, n, score(board)]
    return []

           

numbers, boards = get_input(open("input").readlines())            
x = max(finish(numbers, b) for b in boards)
print(x)
print("b: ", x[1]*x[2])
not 4512

# def worst_board(random_numbers, boards):
#     if(len(boards)<=1):
#         return random_numbers, boards[0]
#     else:
#         for board in boards:
#             apply(board,random_numbers[0])
#         return worst_board(random_numbers[1:], [b for b in boards if not done(b)])


# def solution_b(random_numbers, boards):
#     random_numbers, boards = get_input(open("input").readlines())
#     numbers, worst_board = worst_board(random_numbers, boards);
#     assert(not done(worst_board))
#     for n in numbers:
#         apply(worst_board, n)
#         if(done(worst_board)):
#             return n*score(worst_board)
        
    


# print("b: ", solution_b(*get_input()))
