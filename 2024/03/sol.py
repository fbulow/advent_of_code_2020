import unittest
import re
self = unittest.TestCase

raw = open("input").readlines()

line="xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))"
#re.findall("mul\([0-9][0-9]?[0-9]?,[0-9][0-9]?[0-9]?\)", line)

def mul(s):
    _, a, b = s.replace(',', ' ').replace('(', ' ').replace(')', ' ').split()
    return int(a)*int(b)

def line_value(line): return sum(mul(x) for x in re.findall("mul\\([0-9][0-9]?[0-9]?,[0-9][0-9]?[0-9]?\\)", line))
    



def solA():
    return sum(line_value(line) for line in open("input").readlines())
print(solA())


def commands(line):
    return re.findall("mul\\([0-9][0-9]?[0-9]?,[0-9][0-9]?[0-9]?\\)|do\\(\\)|don't\\(\\)", line)

def eval_commands(commands):
    ret = 0
    active = True
    for cmd in commands:
        if cmd == 'do()':
            active = True
        elif cmd == "don't()":
            active = False
        elif active:
            ret += mul(cmd)
    return ret

def all_commands(lines):
    return sum((commands(line) for line in lines), start = [])
def solB():
    return eval_commands(all_commands(open("input").readlines()))


class Test_(unittest.TestCase):
    def test_mul(self):
        self.assertEqual(8, mul('mul(2,4)'))
        self.assertEqual(88, mul('mul(11,8)'))
    def test_line_value(self):
        self.assertEqual(161, line_value(line))
    def test_line_value_b(self):
        self.assertEqual(48, line_value_b("xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"))
    def test_solA(self):
        self.assertEqual(167090022, solA())
    def test_solB(self):
        self.assertNotEqual(93994894, solB())
        
print(solB())    

