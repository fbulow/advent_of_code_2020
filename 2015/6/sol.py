

def grid():
    ret = dict()
    for r in range(1000):
        for c in range(1000):
            ret[(r,c)]=False
    return ret

on = "on"
off = "off"
toggle = "toggle"

def coord(s):
    x, y = s.split(",")
    return (int(x), int(y))    

class Inst():
    def __init__(self, row):
        if "turn on" in row:
            self.cmd=on
        elif "turn off" in row:
            self.cmd=off
        else:
            self.cmd=toggle
        a,b = (corner for corner in row.split() if "," in corner)
        self.top_left=coord(a)
        self.bottom_right=coord(b)
    def coords(self):
        for r in range(self.top_left[0], 1+self.bottom_right[0]):
            for c in range(self.top_left[1], 1+self.bottom_right[1]):
                yield (r,c)

    def apply(self, grid):
        if self.cmd == on:
            for c in self.coords():
                g[c]=True
        elif i.cmd == off:
            for c in self.coords():
                g[c]=False
        else:
            for c in self.coords():
                g[c] = not(g[c])
    
assert(
    Inst("turn on 489,959 through 759,964").cmd == on)
assert(
    Inst("turn off 489,959 through 759,964").cmd == off)
assert(
    Inst("toggle 489,959 through 759,964").cmd == toggle)

assert(
    Inst("toggle 489,959 through 759,964").top_left == (489,959))
assert(
    Inst("toggle 489,959 through 759,964").bottom_right == (759,964))


g = grid()
for i in (Inst(row) for row in open("input")):
    i.apply(g)
        
print(sum(int(v) for k,v in g.items()))
