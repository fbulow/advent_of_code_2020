
filename='/home/fbulow/github/advent_of_code_2020/2023/11/input'

def isGalaxy(char):
    return char in "#"

def coords(input):
    def ret(rows):
        for ir, row in enumerate(rows):
            for ic, char in enumerate(row):
                if isGalaxy(char):
                    yield (ir, ic)

    return set(x for x in ret(input))

def emptyRows(cset):
    rows = set(x[0] for x in cset)
    return set(q for q in set(x for x in range(max(rows))) if not q in rows)

def _transpose(cset):
    return ((j,i) for i,j in cset)

def emptyCols(cset):
    return emptyRows(_transpose(cset))

def distance(a, b):
    return sum(abs(i-j) for i,j in zip(a,b))

def crossedEmpty(start, end, empty):
    if start > end:
        return crossedEmpty(end, start, empty)
    return (x for x in range(start+1, end) if x in empty)

def allPairs(allGalaxies):
    a = [x for x in allGalaxies]
    for i in range(len(a)):
        for j in range(i+1,len(a)):
            yield (a[i], a[j])

def solA(input, factor=1):
    c = coords(input)
    e = (emptyRows(c), emptyCols(c))
    return sum(distance(a,b)+
               sum(factor for z in crossedEmpty(a[0], b[0], e[0]))+
               sum(factor for z in crossedEmpty(a[1], b[1], e[1])) for a,b in allPairs(c))
        
def solB(input):
    return solA(input, 1000000-1)

import unittest

class Test(unittest.TestCase):
    def test_solA(self):
        self.assertEqual(374,
                         solA(["...#......",
                               ".......#..",
                               "#.........",
                               "..........",
                               "......#...",
                               ".#........",
                               ".........#",
                               "..........",
                               ".......#..",
                               "#...#....."]))                        
    def test_allPairs(self):
        self.assertEqual(36,
                         len(set(x for x in allPairs(range(9)))))
    def test_crossedEmpty(self):
        self.assertEqual(
            tuple(crossedEmpty(1,5, (0,3,4,11))),
            (3,4)
        )
    def test_distance(self):
        self.assertEqual(distance((0,0), (1,2)), 3)
    def test_coords(self):
        self.assertEqual(
            coords(['.#']),
            {(0,1)})
    def test_emptyRows(self):
        self.assertEqual(
            emptyRows({(1,1)}),
            set([0]))
    def test_emptyCols(self):
        self.assertEqual(
            emptyCols({(1,1), (1,3)}),
            set([0,2]))
        
        
if __name__ == '__main__':
    print("SolA:", solA(open('/home/fbulow/github/advent_of_code_2020/2023/11/input').readlines()))
    print("SolB:", solB(open('/home/fbulow/github/advent_of_code_2020/2023/11/input').readlines()))
    unittest.main()
