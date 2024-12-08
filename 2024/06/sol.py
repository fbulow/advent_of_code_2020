from unittest import TestCase, main
import re
import pdb

self = TestCase

def puzzle_input(filename="input"):
    with open(filename,'r') as f:
        return [x.strip() for x in f.readlines()]

def get_choord(char, lines):
    for row, line in enumerate(lines):
        for col, c in enumerate(line):
            if char == c:
                yield row, col


def prep(lines):
    dir = (-1,0)
    pos = next(get_choord('^', lines))
    obstacles = set(get_choord('#', lines))
    floor = set(get_choord('.', lines))
    floor.add(pos)
    return {"dir":dir,
            "pos":pos,
            "obstacles" :obstacles,
            "floor" : floor}
            
                
def solA(lines):    
    return len(visited(**prep(lines)))

def visited(pos, dir, obstacles, floor):
    visited = set()
    while pos in floor:
        visited.add(pos)
        nxt = (pos[0]+dir[0], pos[1]+dir[1])
        if nxt in obstacles:
            dir = { (-1,0): (0,1),
                    (0,1) : (1,0),
                    (1,0) : (0,-1),
                    (0,-1): (-1,0) }[dir]
        else:
            pos=nxt
    return visited

def is_loop(pos, floor, obstacles):
    dir = (-1,0)
    previous = set()
    while pos in floor:
        nxt = (pos[0]+dir[0], pos[1]+dir[1])
        if nxt in obstacles:
            dir = { (-1,0): (0,1),
                    (0,1) : (1,0),
                    (1,0) : (0,-1),
                    (0,-1): (-1,0) }[dir]
        else:
            pos=nxt
        if (pos, dir) in previous:
            return True
        else:
            previous.add((pos, dir))
    return False

def candidates(pos, **arg):
    return (x for x in visited(pos=pos, **arg) if x!=pos)
    

def solB(lines):
    ret = 0
    arg = prep(lines)
    for c in candidates(**arg):
        floor = set((x for x in arg["floor"] if not x==c))
        obstacles = set((x for x in arg["obstacles"]))
        obstacles.add(c)
        
        if is_loop(arg["pos"], floor, obstacles):
            ret+=1
    return ret

class Test_(TestCase):
    def test_solB(self):
        self.assertEqual(
            6,
            solB(puzzle_input('example')))
    def test_solA(self):
        self.assertEqual(
            41,
            solA(puzzle_input('example')))
    def test_(self):
        self.assertEqual(
            [(0,2), (1,0)],
            list(get_choord('x', '..x. x...'.split())))


print(f"A: {solA(puzzle_input())}")
print(f"B: {solB(puzzle_input())}")
#main()


