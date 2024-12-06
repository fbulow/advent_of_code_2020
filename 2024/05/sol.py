from unittest import TestCase, main
import re
import pdb

self = TestCase

def puzzle_input(filename="input"):
    with open(filename,'r') as f:
        return [x.strip() for x in f.readlines()]

def moves_and_sequences(lines):
    N = next(i for i,x in enumerate(lines) if x=="")
    return [tuple(int(q) for q in x.split('|')) for x in lines[:N]],\
        [tuple((int(x) for x in line.split(','))) for line in lines[N+1:]]

def in_sequence(moves, sequence):
    for ab in moves:
        try:
            ia, ib = (sequence.index(x) for x in ab)
            if ia > ib:
                return False
        except ValueError:
            pass
    return True

def middle_value(sequence):
    return sequence[len(sequence)//2]

def solA(lines):
    m,s  = moves_and_sequences(lines)
    return sum(middle_value(x) for x in s if in_sequence(m, x))

def solB(lines):
    pass


class Test_(TestCase):
    def test_data(self):
        moves, seq = moves_and_sequences(puzzle_input('input'))
        self.assertTrue(all(len(set(x))==len(x) for x in seq))
        self.assertTrue(all((b,a) not in moves for a,b in moves))

        self.assertEqual(moves[0], (39, 46))
        self.assertEqual(moves[-1], (42,77))

        self.assertEqual(seq[0], (94,28,25,26,39))
        self.assertEqual(seq[-1], (19,44,72,23,94,14,74,62,42,85,27,61,29,28,11,89,75,57,25,81,69,53,98))
        
    def test_solA_failed(self):
        self.assertEqual(143, solA(puzzle_input('example')))
        self.assertNotEqual(1344, solA(puzzle_input()))
        self.assertGreater(10888, solA(puzzle_input()))
        print(f"A: {solA(puzzle_input())}")

    def test_middle_value(self):
        self.assertEqual(
            3,
            middle_value([1,2,3,4,5]))
    def test_in_sequence(self):
        moves, seq = moves_and_sequences(puzzle_input('example'))
        self.assertEqual(
            [True,True,True, False,False,False,],
            [in_sequence(moves, x) for x in seq])

    def test_moves_and_sequences(self):
        a,b = moves_and_sequences(["1|2", "", "1,2,3"])
        self.assertEqual(a,[(1,2)])
        self.assertEqual(b,[(1,2,3)])


print(f"B: {solB(puzzle_input())}")
#main()


