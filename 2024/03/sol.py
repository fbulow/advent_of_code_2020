from unittest import TestCase
import re
self = TestCase

def puzzle_input():
    with open("input",'r') as f:
        return f.readlines()

def mul(s):
    _, a, b = s.replace(',', ' ').replace('(', ' ').replace(')', ' ').split()
    return int(a)*int(b)

def line_value(line):
    regex = "mul\\([0-9][0-9]?[0-9]?,[0-9][0-9]?[0-9]?\\)"
    return sum(mul(x) for x in re.findall(regex, line))

def solA(lines = puzzle_input()):
    return sum(line_value(line) for line in lines)

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
def solB(lines = puzzle_input()):
    return eval_commands(all_commands(lines))


class Test_(TestCase):
    def test_mul(self):
        self.assertEqual(8, mul('mul(2,4)'))
        self.assertEqual(88, mul('mul(11,8)'))
    def test_line_value(self):
        self.assertEqual(161, line_value("xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))"))
    def test_line_value_b(self):
        self.assertEqual(48, solB(["xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"]))
    def test_solA(self):
        self.assertEqual(167090022, solA())
    def test_solB(self):
        self.assertNotEqual(93994894, solB())
        
print(f"A: {solA()}")
print(f"B: {solB()}")

