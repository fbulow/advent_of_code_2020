from unittest import TestCase, main
import re
import pdb

self = TestCase

def puzzle_input(filename="input"):
    with open(filename,'r') as f:
        return [x.strip() for x in f.readlines()]

def rec(result, total, *tail):
    if len(tail) == 0:
        return result == total
    else:
        return \
            rec(result,
                total + tail[0],
                *tail[1:]) or \
            rec(result,
                total * tail[0],
                *tail[1:])
            
def is_repairable(line):
    first, *rest = [int(x) for x in line.replace(':', ' ').split()]
    if rec(*[int(x) for x in line.replace(':', ' ').split()]):
        return first
    else:
        return 0
    
    
def solA(lines):    
    return sum(is_repairable(line) for line in lines)

def solB(lines):
    pass

class Test_(TestCase):
    def test_solA(self):
        self.assertEqual(
            3749,
            solA(puzzle_input('example')))
            
    def test_is_repairable(self):
        self.assertTrue(
            is_repairable("190: 10 19"))
        self.assertFalse(
            is_repairable("83: 17 5"))
        self.assertTrue(
            is_repairable("3267: 81 40 27"))

print(f"A: {solA(puzzle_input())}")
print(f"B: {solB(puzzle_input())}")
#main()


