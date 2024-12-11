from unittest import TestCase, main
import re
import pdb
import sys
self = TestCase

def puzzle_input(filename="input"):
    with open(filename,'r') as f:
        return [x.strip() for x in f.readlines()]

def trans(stone):
    if stone == '0':
        return ['1']
    elif len(stone)%2==0: #Even
        N=len(stone)//2
        return [str(int(stone[:N])), str(int(stone[N:]))]
    else:
        return [str(int(stone)*2024)]
    
def blink(stones):
    return " ".join(sum((trans(stone) for stone in stones.split()), start = []))

    
def solA(lines, N=25):
    line = lines[0]
    for _ in range(N):
        line=blink(line)
    return len(line.split())
    

def solB(lines):
    pass


class Test_(TestCase):
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
        self.assertEqual(['1'], trans('0'))
        self.assertEqual(['2024'], trans('1'))
        self.assertEqual(['20','24'], trans('2024'))
            

