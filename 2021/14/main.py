data = open('input').readlines()
template = data[0].strip()

rules={}
for a,b in [x.strip().split(' -> ') for x in  data[2:]]:
    rules[a]=b
    
def subst(x):
    ret = ""
    for i in range(len(x)-1):
        insertMe = rules.get(x[i:i+2], False)
        if insertMe:
            ret+=x[i]+insertMe
        else:
            ret+=x[i]
    ret+=x[-1]
    return ret


def substNtimes(template, N):
    ans = subst(template)
    for i in range(N-1):
        ans = subst(ans)

    cnt = dict()
    for x in ans:
        cnt[x] = cnt.get(x,0) + 1
    return max(cnt.values()) - min(cnt.values())

assert(substNtimes(template, 10) == 3306)
    
print("a: ", substNtimes(template, 10))


