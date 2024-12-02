import unittest

up=(1,2,3)
down=(-1, -2, -3)

def diffs(line):
    if isinstance(line, str):
        v = list(int(x) for x in line.split())
    else:
        v = line
    return (b-a for a,b in zip(v[:-1], v[1:]))

def all_in(line, accepted):
    return all((x in accepted for x in diffs(line)))

def is_ok(line):
    return all_in(line, up) or all_in(line, down)

def solA(lines=open('input').readlines()):
    return sum(1 for line in lines if is_ok(line))

print(solA())

def remove_any_one_number(line):
    line = list(line.split())
    for i in range(len(line)):
        yield " ".join(line[:i]+line[i+1:])

def is_ok_b(line):
    return is_ok(line) or any(is_ok(x) for x in remove_any_one_number(line))

def solB(lines=open('input').readlines()):
    return sum(1 for line in lines if is_ok_b(line))

print(solB())

class _(unittest.TestCase):
    def test_solB(self):
        self.assertEqual(436, solB())
    def test_ok_b(self):
        self.assertTrue(is_ok_b("7 6 4 2 1"), "Safe without removing any level.")
        self.assertFalse(is_ok_b("1 2 7 8 9"), "Unsafe regardless of which level is removed.")
        self.assertFalse(is_ok_b("9 7 6 2 1"), "Unsafe regardless of which level is removed.")
        self.assertTrue(is_ok_b("1 3 2 4 5"), "Safe by removing the second level, 3.")
        self.assertTrue(is_ok_b("8 6 4 4 1"), "Safe by removing the third level, 4.")
        self.assertTrue(is_ok_b("1 3 6 7 9"), "Safe without removing any level.")

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

    def test_diffs(self):
        self.assertEqual([2], list(diffs("1 3")))
unittest.main()
