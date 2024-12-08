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

def resonant_nodes(a,b, rcount):
    ret = set()
    dx, dy = tuple( p-q for p, q in zip(a,b))
    for _ in range(rcount):
        a = (a[0]+dx, a[1]+dy)
        b = (b[0]-dx, b[1]-dy)
        ret.add(a)
        ret.add(b)
    return ret

def antinodes(a,b):
    return resonant_nodes(a,b, rcount=1)

def take_two(nodes):
    for i in range(len(nodes)-1):
        for j in range(i+1, len(nodes)):
            yield (nodes[i], nodes[j])


def all_antinodes(nodes, **kw):
    for a,b in take_two(nodes):
        for x in resonant_nodes(a,b, **kw):
            yield x

def on_board_fcn(lines):
    Nrows = len(lines)
    Ncols = len(lines[0])
    return lambda row,col: row>=0 and row<Nrows and col>=0 and col<Ncols

def all_all_antinodes(lines, rcount, initial=()):
    """
    all_antinodes for every line in lines also inluding
    coordinates given in  initia.
    """

    ob = on_board_fcn(lines)

    antinodes = set((x for x in initial))
    for nodes in frequency_table(lines).values():
        for n in all_antinodes(nodes, rcount=rcount):
            if ob(*n):
                antinodes.add(n)
    return antinodes

def solA(lines):
    return len(all_all_antinodes(lines, rcount=1))

def solB(lines):
    rcount = max(len(lines), len(lines[0]))

    initial = []
    for antenna_pos in frequency_table(lines).values():
        initial+=antenna_pos
    
    antennas = sum(len(x) for x in frequency_table(lines).values())
    return len(all_all_antinodes(lines, rcount = rcount, initial=initial))


class Test_(TestCase):
    def test_solB(self):
        self.assertEqual(
            34,
            solB(puzzle_input('example')))

    def test_resonant_nodes(self):
        self.assertEqual(
            set(((2,4), (3,6),
                 (-1,-2), (-2,-4))),
            resonant_nodes((0,0), (1,2), 2))

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
                all_antinodes(frequency_table(puzzle_input('example_a'))['a'],
                              rcount=1) \
                if sut(*anode)))
        
    def test_all_antinodes(self):
        nodes = frequency_table(puzzle_input('example_a'))['a']
        self.assertEqual(
            6,
            len(set(all_antinodes(nodes, rcount=1))))
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
