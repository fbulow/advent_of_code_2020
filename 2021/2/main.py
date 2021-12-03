#!/usr/bin/python3

data = ( x.split() for x in open("input").readlines())
data = [(a, int(b)) for a,b in data]

up='up'
down='down'
forward='forward'

def s(key):
    return sum(b for a,b in data if a==key) 

print("a: ", s(forward) * (s(down)-s(up)))

aim = 0
depth = 0
for a,b in data:
    if  a==down:
        aim+= b
    if  a==up:
        aim-= b
    elif a==forward:
        depth+= aim*b

print("b: ", s(forward)*depth)
