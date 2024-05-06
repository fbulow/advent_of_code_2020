import unittest

filename='/home/fbulow/github/advent_of_code_2020/2023/11/input'

def asMap(iterateOverRowStrings):
    def f(iterateOverRowStrings):
        for row, s in enumerate(iterateOverRowStrings):
            for col, char in enumerate(s):
                if char=='#':
                    yield (row, col)
    return {x for x in f(iterateOverRowStrings)}

class Sol(unittest.TestCase):
    def test_as_set(self):
        #                        01234
        self.assertEqual(asMap(["...#......"]),
                         {(0,3)})
        self.assertEqual(asMap(["...#.#...."]),
                         {(0,3), (0,5)})
        self.assertEqual(asMap(["#...",
                                "...#.#...."]),
                         {(0,0), (1,3), (1,5)})

if __name__=='__main__':
    unittest.main()
