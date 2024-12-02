import unittest

def as_ints(line):
    return (int(x) for x in line.split())

def diffs(line):
    v = list(as_ints(line))
    return (b-a for a,b in zip(v[:-1], v[1:]))

def is_ok_increaseing(line):
    return all((x in (1,2,3) for x in diffs(line)))

def is_ok_decreaseing(line):
    return all((x in (-1,-2,-3) for x in diffs(line)))

def is_ok(line):
    return is_ok_increaseing(line) or is_ok_decreaseing(line)

def solA(lines=open('input').readlines()):
    return sum(1 for line in lines if is_ok(line))

print(solA())

class _(unittest.TestCase):
    def test_solA(self):
        self.assertEqual(383, solA())
    def test_is_ok(self):
        #Safe because the levels are all decreasing by 1 or 2.
        self.assertTrue(is_ok("7 6 4 2 1"))
        #Unsafe because 2 7 is an increase of 5.
        self.assertFalse(is_ok("1 2 7 8 9"))
        #Unsafe because 6 2 is a decrease of 4.
        self.assertFalse(is_ok("9 7 6 2 1"))
        #Unsafe because 1 3 is increasing but 3 2 is decreasing.
        self.assertFalse(is_ok("1 3 2 4 5"))
        #Unsafe because 4 4 is neither an increase or a decrease.
        self.assertFalse(is_ok("8 6 4 4 1"))
        #Safe because the levels are all increasing by 1, 2, or 3.
        self.assertTrue(is_ok("1 3 6 7 9"))

    def test_as_ints(self):
        self.assertEqual([1], list(as_ints("1")))
    def test_as_ints(self):
        self.assertEqual([1,2], list(as_ints("1 2")))
    def test_diffs(self):
        self.assertEqual([2], list(diffs("1 3")))
unittest.main()
