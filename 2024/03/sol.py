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
    

class Test_(unittest.TestCase):
    def test_mul(self):
        self.assertEqual(8, mul('mul(2,4)'))
        self.assertEqual(88, mul('mul(11,8)'))
    def test_line_value(self):
        self.assertEqual(161, line_value(line))


def solA():
    return sum(line_value(line) for line in open("input").readlines())
print(solA())        
unittest.main()
