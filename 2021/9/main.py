
floormap = ["9"+row.strip()+"9" for row in open("input").readlines()]
frame = ["9"*len(floormap[0])]
floormap = frame + floormap + frame

def point(row, col, fm):
    return floormap[row][col]

def lowpoint(row, col, fm):
    p = point(row, col, fm)
    return ( p < floormap[row-1][col]) and \
           ( p < floormap[row+1][col]) and \
           ( p < floormap[row][col-1]) and \
           ( p < floormap[row][col+1])


low_points = []
for row in range(1, len(floormap)-1):
    for col in range(1, len(floormap[0])-1):
        if lowpoint(row, col, floormap):
            low_points.append(floormap[row][col])
            
def sol_a(low_points):
    return sum(int(x)+1 for x in low_points)

print(sol_a(low_points))
assert(sol_a(low_points) > 510)
