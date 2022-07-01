#!/usr/bin/python3

def input():
    ret = open("input").readlines();
    assert(len(ret)==1)
    return ret[0]

def count(char="("):
    return sum( 1 for x in input() if x==char )

print( count("(")-count(")") )


def findFirst(inp):
level=0
for char, ret in zip(inp, range(len(input))):
    level=level+dict([("(", 1), (")", -1)])[char]
    if(level==-1):
        return ret+1

    
