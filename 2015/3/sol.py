m = { '>' : (1,0),
      '<' : (-1,0),
      '^' : (0,1),
      'v' : (0,-1) }

chars = open("input").readline().strip()

def inst(chars): return (m[c] for c in chars)

def ag(inst):
    pos = (0,0)
    yield pos
    for x,y in inst:
        pos = (x+pos[0], y+pos[1])
        yield pos
        

def doubles(places):
    seen = set()
    for p in places:
        if p in seen:
            yield p
        else:
            seen.add(p)

print(len(set(ag(inst(chars)))))


def oe(inst,d): return (x for i, x in enumerate(inst) if i%2==d)
def even(inst): return oe(inst,1)
def odd(inst): return oe(inst,0)
    
print(len(set(ag(inst(odd(chars)))).union(set(ag(inst(even(chars)))))))
