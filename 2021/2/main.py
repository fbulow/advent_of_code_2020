#!/usr/bin/python3

data = ( x.split() for x in open("input").readlines())
data = [(a, int(b)) for a,b in data]

h = sum(b for a,b in data if a=='forward')
v = sum(b for a,b in data if a=='down') - sum(b for a,b in data if a=='up')

print(h*v)


aim = 0
depth = 0
for a,b in data:
    if  a=='down':
        aim = aim+b
    if  a=='up':
        aim = aim-b
    elif a=='forward':
        depth = depth + aim*b

print(h*depth)
