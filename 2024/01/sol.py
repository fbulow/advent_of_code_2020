a=[]
b=[]

for A,B in (x.split() for x in open("./input").readlines()):
    a.append(int(A))
    b.append(int(B))

print(sum(abs(x-y) for x,y in  zip(sorted(a), sorted(b))))


count = dict()
for x in b:
    count[x] = 1+count.get(x, 0)
print(sum(x*count.get(x,0) for x in a))
