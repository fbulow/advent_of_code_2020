from unittest import TestCase, main
import re
import pdb
import sys
self = TestCase

def puzzle_input(filename="input"):
    with open(filename,'r') as f:
        return [x.strip() for x in f.readlines()]

all_directions= tuple((int(z.real), int(z.imag)) for\
                      z in (1j,
                            1j*1j,
                            1j*1j*1j,
                            1j*1j*1j*1j))
    
def trail(lines, row, col, should_be=0):
    if (row<0) or (col<0):
        return []
    try:
        c = lines[row][col]
    except IndexError:
        return []
    if c == str(should_be):
        if c == '9':
            return [(row, col)]
        else:
            return sum(
                (trail(lines, row+dr, col+dc, should_be+1)
                 for dr, dc in all_directions), start = [])
    else:
        return []
    
def solA(lines):
    ret = 0
    for row in range(len(lines)):
        for col in range(len(lines[0])):
            ret += len(set(trail(lines, row, col)))
    return ret

def solB(lines):
    None

class Test_(TestCase):
    def test_solA(self):
        self.assertEqual(
            2,
            solA(["...0...",
                  "...1...",
                  "...2...",
                  "6543456",
                  "7.....7",
                  "8.....8",
                  "9.....9"])
        )
        self.assertEqual(
            4,
            solA(["..90..9",
                  "...1.98",
                  "...2..7",
                  "6543456",
                  "765.987",
                  "876....",
                  "987....",]))
        # self.assertEqual(
        #     36,
        #     solA(puzzle_input('example')))

ret_a = solA(puzzle_input('input'))        
print(f"A: {ret_a}")
if(ret_a>=1530):
    print( "A to big")

# ret_b = solB(puzzle_input('input'))
# print(f"B: {ret_b}")
# #main()
