from unittest import TestCase, main
import re
import pdb
import sys
import math

self = TestCase

def puzzle_input(filename="input"):
    with open(filename,'r') as f:
        return [x.strip() for x in f.readlines()]

def strlen(stone):
    if stone==0:
        return 1
    return 1+int(math.log(stone)/math.log(10))
    
def trans(stone):
    if stone == 0:
        return [1]
    elif strlen(stone)%2==0: #Even
        stone = str(stone)
        N=len(stone)//2
        return [int(stone[:N]), int(stone[N:])]
    else:
        return [int(stone)*2024]
    
def blink(stones):
    seq = sum((trans(int(stone)) for stone in stones.split()), start = [])
    return " ".join((str(x) for x in seq))

    
def solA(lines, N=25):
    line = lines[0]
    return sum((contrib(int(x), N) for x in lines[0].split()))

def contrib(stone, levels, cache=dict()):
    try:
        return cache[(stone,levels)]
    except KeyError:
        if levels == 0:
            ret = 1
        else:
            ret = sum(contrib(xx, levels-1) for xx in trans(stone))
        cache[(stone,levels)] = ret
        return ret

class Test_(TestCase):
    def test_contrib(self):
        self.assertEqual(
            1,
            contrib(None, 0))
        self.assertEqual(
            2,
            contrib(10, 1))
    def test_strlen(self):
        self.assertEqual(
            1,
            strlen(0))
        self.assertEqual(
            1,
            strlen(1))
        self.assertEqual(
            1,
            strlen(2))
        self.assertEqual(
            2,
            strlen(10))
        self.assertEqual(
            3,
            strlen(100))
        
    def test_solA(self):
        self.assertEqual(
            22,
            solA(["125 17"], 6))
        self.assertEqual(
            55312,
            solA(["125 17"], 25))

    def test_blink(self):
        self.assertEqual(
            "1 2024 1 0 9 9 2021976",
            blink("0 1 10 99 999"))
    def test_trans(self):
        self.assertEqual([1], trans(0))
        self.assertEqual([2024], trans(1))
        self.assertEqual([20, 24], trans(2024))


