#!/usr/bin/python3

d=[int(x) for x in open("input").readlines()]
for upg, i in [("a",1),("b",3)]:
    print(upg, ": ", sum(int(b>a) for a,b in zip(d[:-i], d[i:])))
