from unittest import TestCase, main
import re
import pdb

self = TestCase

def puzzle_input(filename="input"):
    with open(filename,'r') as f:
        return [x.strip() for x in f.readlines()]



lines = puzzle_input()
def frequency_table(lines):
    ret = dict()
    for row, line in enumerate(lines):
        for col, char in enumerate(line):
            if char!='.':
                ret[char] = ret.get(char, [])+[(row, col)]
    return ret

def antinodes(a,b):
    dx, dy = tuple( p-q for p, q in zip(a,b))
    return set(((a[0]+dx, a[1]+dy), (b[0]-dx, b[1]-dy)))

def take_two(nodes):
    for i in range(len(nodes)-1):
        for j in range(i+1, len(nodes)):
            yield (nodes[i], nodes[j])


def all_antinodes(nodes):
    for a,b in take_two(nodes):
        for x in antinodes(a,b):
            yield x

def on_board_fcn(lines):
    Nrows = len(lines)
    Ncols = len(lines[0])
    return lambda row,col: row>=0 and row<Nrows and col>=0 and col<Ncols

def solA(lines):
    ob = on_board_fcn(lines)

    antinodes = set()
    for nodes in frequency_table(lines).values():
        for n in all_antinodes(nodes):
            if ob(*n):
                antinodes.add(n)
    return len(antinodes)

def solB(lines):
    pass

class Test_(TestCase):
    def test_solA(self):
        self.assertEqual(
            14,
            solA(puzzle_input('example')))
        
    def test_on_board_fcn(self):
        lines = puzzle_input('example_a')
        sut = on_board_fcn(lines)
        self.assertEqual(
            4,
            sum(1 for anode in \
                all_antinodes(frequency_table(puzzle_input('example_a'))['a']) \
                if sut(*anode)))
        
    def test_all_antinodes(self):
        nodes = frequency_table(puzzle_input('example_a'))['a']
        self.assertEqual(
            6,
            len(set(all_antinodes(nodes))))
    def test_take_two(self):
        self.assertEqual(
            set((('a','b'), ('a','c'), ('b','c'))),
            set(take_two("a b c".split())))

    def test_antinodes(self):
        self.assertEqual(
            set(((-1,-2), (2, 4))),
            antinodes((0,0), (1,2)))


print(f"A: {solA(puzzle_input('input'))}")
print(f"B: {solB(puzzle_input('input'))}")
#main()


