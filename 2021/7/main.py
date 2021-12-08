#!/usr/bin/python3

data = [int(x) for x in open("input").readline().split(",")]


pos = [16,1,2,0,4,2,7,1,2,14]
def cost(target, pos):
    return sum(abs(target - p) for p in pos)

def possible(pos):
    return range(min(pos), max(pos)+1)


def solution_a(pos):
    return min(cost(t, pos) for t in possible(pos))


def linear_cost(n):
    return n*(n+1)//2

assert(linear_cost(1)==1)
assert(linear_cost(2)==3)
assert(linear_cost(3)==6)
    
def costb(target, pos):
    return sum(linear_cost(abs(target - p)) for p in pos)

def solution_b(pos):
    return min(costb(t, pos) for t in possible(pos))
        
print("a: ", solution_a(data))
print("b: ", solution_b(data))





