import pdb
filename = "input"
#filename = "example"

floormap = ["9"+row.strip()+"9" for row in open(filename).readlines()]
frame = ["9"*len(floormap[0])]
floormap = frame + floormap + frame
floormap = [[x for x in row] for row in floormap]


def counted(row, col, fm):
     return fm[row][col] == " "

def edge(row, col, fm):
     return fm[row][col] == "9"
    

def flood_fill(row, col, fm):
    if edge(row, col, fm) or counted(row, col, fm):
        return 0
    else:
        fm[row][col]=' '
        return 1+sum(flood_fill(*coord, fm) for coord in [[row-1, col],
                                                          [row+1, col],
                                                          [row, col-1],
                                                          [row, col+1]])

basins = []
for row in range(1, len(floormap)-1):
    for col in range(1, len(floormap[0])-1):
        x = flood_fill(row, col, floormap)
        if x>0:
            basins.append(x)

x = sorted(basins)[-3:]
print(x[0]*x[1]*x[2])
