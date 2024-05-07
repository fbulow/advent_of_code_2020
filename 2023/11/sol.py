import unittest

filename='/home/fbulow/github/advent_of_code_2020/2023/11/input'

def asSet(iterateOverRowStrings):
    def f(iterateOverRowStrings):
        for row, s in enumerate(iterateOverRowStrings):
            for col, char in enumerate(s):
                if char=='#':
                    yield (row, col)
    return {x for x in f(iterateOverRowStrings)}

def initialDistance(start, end):
    return sum(abs(a-b) for a,b in zip(start, end))

def countCrossed(start, end, shouldBeCounted):
    return sum(1 for x in range(start, end) if x in shouldBeCounted)

def emptySpaces(notEmpty):
    return set(i for i in range(min(notEmpty), max(notEmpty)+1) if not i in notEmpty)


class Sol(unittest.TestCase):
    def test_emptySpaces(self):
        self.assertEqual({2,4}, emptySpaces({0,1,3,5}))
    def setUp(self):
        self.exampleMap=asSet(open('/home/fbulow/github/advent_of_code_2020/2023/11/example')
                              .readlines())

    def test_as_set(self):
        #                        01234
        self.assertEqual(asSet(["...#......"]),
                         {(0,3)})
        self.assertEqual(asSet(["...#.#...."]),
                         {(0,3), (0,5)})
        self.assertEqual(asSet(["#...",
                                "...#.#...."]),
                         {(0,0), (1,3), (1,5)})
    def test_initialDistance(self):
        self.assertEqual(5,
                         initialDistance((0,0), (2,3)))
    def test_countCrossed(self):
        self.assertEqual(2, countCrossed(0, 5, {2,3}))

if __name__=='__main__':
    unittest.main()
