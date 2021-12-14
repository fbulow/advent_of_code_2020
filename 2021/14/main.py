import pdb
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
    return cnt

def answer(cnt):
    return max(cnt.values()) - min(cnt.values())



assert(answer(substNtimes(template, 10)) == 3306)
    
print("a: ", answer(substNtimes(template, 10)))

def keyCount(template):
    x= template
    ret=dict()
    for i in range(len(template)-1):
        key = x[i:i+2]
        ret[key]= ret.get(key,0)+1
    return ret

def elementCount(keyCount):
    twice = {}
    for key in keyCount:
        for letter in key:
            twice[letter] = twice.get(letter,0)+keyCount[key]
    for key in twice:
        twice[key]= twice[key]//2 +twice[key]%2
    return twice


def step(kc):
    ret=dict()
    for key in kc:
        a = key[0]+rules[key]
        b = rules[key]+key[1]
        if a in rules:
            ret[a] = ret.get(a,0)+kc[key]
        if b in rules:
            ret[b] = ret.get(b,0)+kc[key]
    return ret
        
def stepTemplate(template,N):
    kc = keyCount(template)
    for i in range(N):
        kc = step(kc)
    return kc

print(answer(elementCount(stepTemplate(template, 40))))
