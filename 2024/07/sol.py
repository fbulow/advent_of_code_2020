from unittest import TestCase, main
import re
import pdb

self = TestCase

def puzzle_input(filename="input"):
    with open(filename,'r') as f:
        return [x.strip() for x in f.readlines()]

def add(a,b):
    if not ((isinstance(a,int)) and (isinstance(b,int))):
        pdb.set_trace()
    return a+b

def mul(a,b):
    if not ((isinstance(a,int)) and (isinstance(b,int))):
        pdb.set_trace()
    return a*b
    
def joina(a,b):
    return int(str(a)+str(b))
    
def rec(result, total, *tail,
        operators = [add, mul]):
                     
    if len(tail) == 0:
        return result == total
    else:
        for val in (f(total, tail[0]) for f in operators):
            if rec(result, val, *tail[1:], operators = operators):
                return True
        return False
    
def is_repairable(line, **kw):
    first, *rest = [int(x) for x in line.replace(':', ' ').split()]
    if rec(*[int(x) for x in line.replace(':', ' ').split()], **kw):
        return first
    else:
        return 0
    
def solA(lines):    
    return sum(is_repairable(line) for line in lines)

def solB(lines):
    return sum(is_repairable(line, operators=[add, mul, joina]) for line in lines)

class Test_(TestCase):
    def test_solB(self):
        self.assertEqual(
            11387,
            solB(puzzle_input('example')))
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


