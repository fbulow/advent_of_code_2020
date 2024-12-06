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
    
def solA(lines):
    dir = (-1,0)
    pos = next(get_choord('^', lines))
    obstacles = set(get_choord('#', lines))
    floor = set(get_choord('.', lines))
    floor.add(pos)
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
    return len(visited)

def solB(lines):
    pass
class Test_(TestCase):
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


