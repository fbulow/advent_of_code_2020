from unittest import TestCase
import re
self = TestCase

def puzzle_input():
    with open("input",'r') as f:
        return f.readlines()

def _transpose(lines):
    for col in range(len(lines[0])):
        yield "".join(row[col] for row in lines)
def transpose(lines):
    return list(_transpose(lines))
def diagonal_indices(rows, columns, diagonal):
    for r in range(rows):
        for c in range(columns):
            if diagonal == r+c:
                yield (r,c)
def all_diagonals(lines):
    rows = len(lines)
    cols = len(lines[0])
    for i in range(len(lines)+len(lines[0])-1):
        yield "".join(lines[r][c] for r,c in diagonal_indices(rows, cols, i))

def diagonals(lines):
    return list(all_diagonals(lines))
        
def mirror(lines):
    return ["".join(reversed(s)) for s in lines]

def _count_xmas(lines):
    return sum(len(re.findall("XMAS", line)) for line in lines)
def count_xmas(lines):
    return _count_xmas(lines)+_count_xmas(mirror(lines))


def solA(lines = puzzle_input()):
    return sum((
        count_xmas(lines),
        count_xmas(transpose(lines)),
        count_xmas(diagonals(lines)),
        count_xmas(diagonals(mirror(lines)))
        ))


def A_counts(row, col, lines):
    return all(lines[r][c]==char for char, r, c in\
               (('M', row-1, col-1),
                ('S', row-1, col+1),
                ('A', row, col),
                ('M', row+1, col-1),
                ('S', row+1, col+1),
                ))

def count_all_example_x(lines):
    ret = 0
    for row in range(1, len(lines)-1):
        for col in range(1, len(lines[0])-1):
            if A_counts(row, col, lines):
                ret+=1
    return ret
            

def solB(lines = puzzle_input()):
    return count_all_example_x(lines) +\
        count_all_example_x(mirror(lines)) +\
        count_all_example_x(transpose(mirror(lines))) +\
        count_all_example_x(mirror(transpose(lines)))


class Test_(TestCase):
    def test_solB(self):
        self.assertEqual(9,
                         solB([".M.S......",
                              "..A..MSMS.",
                              ".M.S.MAA..",
                              "..A.ASMSM.",
                              ".M.S.M....",
                              "..........",
                              "S.S.S.S.S.",
                              ".A.A.A.A..",
                              "M.M.M.M.M.",
                               ".........."]))

                         
    def test_A_counts(self):
        self.assertTrue(
            A_counts(1, 1, "M.S .A. M.S".split()))
        self.assertFalse(
            A_counts(1, 1, "M.S .A. M..".split()))
        self.assertFalse(
            A_counts(1, 1, "M.S .A. ...".split()))
        self.assertFalse(
            A_counts(1, 1, "M.S ... ...".split()))
        self.assertFalse(
            A_counts(1, 1, "M.. ... ...".split()))
        self.assertFalse(
            A_counts(1, 1, "... ... ...".split()))



    def test_solA(self):
        self.assertEqual(1 , 
                         solA(["....X.",
                               "...M..",
                               "..A...",
                               ".S....",
                               "......"]))
        self.assertEqual(1 , 
                         solA([".X....",
                               "..M...",
                               "...A..",
                               "....S.",
                               "......"]))
        self.assertEqual(1 , 
                         solA([".X....",
                               ".M....",
                               ".A....",
                               ".S....",
                               "......"]))
        self.assertEqual(1 , 
                         solA(["......",
                               "......",
                               ".XMAS.",
                               "......",
                               "......"]))

    def test_count_xmas(self):
        self.assertEqual(1, count_xmas([" XMAS"]))
        self.assertEqual(2, count_xmas([" XMAS XMAS"]))
                        
    def test_mirror(self):
        self.assertEqual("cba gfe".split(),
                         mirror("abc efg".split()))
        
    def test_all_diagonals(self):
        self.assertEqual(set(("a", "bd", "ce", "f")),
                         set(all_diagonals("abc def".split())))

    def test_diagonal_indices(self):
        self.assertEqual(set([(0,0)]),
                         set(diagonal_indices(2, 2, 0)))
        self.assertEqual(set([(1,0), (0,1)]),
                         set(diagonal_indices(2, 2, 1)))

    def test_transpose(self):
        self.assertEqual(["ab"],
                         list(transpose(["a", "b"])))
                         
        
    # def test_diagonals(self):
    #     self.assertEqual("c ad b".split(),
    #                      list(diagonals(["ab", "cd"])))
        


        
print(f"A: {solA()}")
print(f"B: {solB()}")

