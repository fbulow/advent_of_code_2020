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
    pass
def solB(lines):
    pass


class Test_(TestCase):
    def test_solA(self):
        self.assertEqual(1,1)

