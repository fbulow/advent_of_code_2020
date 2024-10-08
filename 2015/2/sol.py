

dim = tuple(tuple(int(a) for a in x.strip().split("x")) for x in open("input") if x)

def area(l, w, h):
    # The elves also need a little extra paper for each present: the area of t
    sides = (l*w, w*h, h*l)
    return 2*sum(x for x in sides)+min(sides)

print( sum(area(*x) for x in dim) )

def perimeter(a,b): return 2*(a+b)

def bow(l, w, h): return l*w*h

def ribbon(l, w, h):
    return bow(l,w,h) + min(perimeter(a,b) for a,b in ((l,w), (l,h), (w,h)))

print(ribbon(2,3,4))    
print(ribbon(1,1,10))    

print( sum(ribbon(*x) for x in dim) )
