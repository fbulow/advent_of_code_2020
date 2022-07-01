import pdb
from sympy import *
lin = [x.strip() for x in open("input").readlines()]

a = [i for i, x in enumerate(lin) if x == 'inp w']
groups = [lin[i:j] for i,j in zip(a[:-1], a[1:])]
groups.append(lin[a[-1]:])

def pattern(group):
    return [" ".join(l.split()[:2]) for l in group]

def anti_pattern(group):
    return [" ".join(l.split()[2:]) for l in group[1:]]

ap = [anti_pattern(g) for g in groups]

for g in groups[1:]:
    assert(pattern(groups[0]) == pattern(g))

def val(w=0, x=0, y=0,z=0):
    return {'w': w, 'x':x, 'y':y, 'z':z}

def iter(n):
    n=str(n)
    return {'w':Symbol('w'+n),
            'x':Symbol('x'+n),
            'y':Symbol('y'+n),
            'z':Symbol('z'+n)}


def foo(line, val=None):
    if(val==None):
        val={'w': 0, 'x':0, 'y':0, 'z':0}
    key, a, b = line.split()
    if b in 'wxyz':
        b= val[b]
    else:
        b = int(b)
    val[a] = {'add' : lambda a,b: a+b,
              'mul' : lambda a,b: a*b,
              'div' : lambda a,b: a//b,
              'mod' : lambda a,b: a%b}[key](val[a], b)
    return val

def bar(lines, val):
    for line in lines:
        val = foo(line, val)
    return val

def choice(group, values = None):
    if values == None:
        values = iter(0)
    a = bar(group[1:6], values)
    def setX(x):
        b=a.copy()
        b["x"]=x
        return bar(groups[0][8:],b)["z"]
    return [setX(0), setX(1), a["x"]]
