import pdb

ex = ["v...>>.vv>",
      ".vv>>.vv..",
      ">>.>v>...v",
      ">>v>>.>.v.",
      "v>v.vv.v..",
      ">.>>..v...",
      ".vv..>.>v.",
      "v.v..>>v.v",
      "....v..v.>"]


def stepRight(before):
    b = [[x for x in r]  for r in before]
    a = [["." for x in range(len(r))]   for r in before] #after
    Nr = len(a)
    Nc = len(a[0])
    for row in range(Nr):
        for col in range(Nc):
            if b[row][col] == ">":
                if "." == b[row][(col+1)%Nc]:
                    a[row][(col+1)%Nc] = ">"
                else:
                    a[row][col%Nc] = ">"
            elif b[row][col] != '.':
                a[row][col] = b[row][col]
    return ["".join(x) for x in a]

def stepDown(before):
    b = [[x for x in r]  for r in before]
    a = [["." for x in range(len(r))]   for r in before] #after
    Nr = len(a)
    Nc = len(a[0])
    for row in range(Nr):
        for col in range(Nc):
            if b[row][col] == "v":
                if "." == b[(row+1)%Nr][col]:
                    a[(row+1)%Nr][col] = "v"
                else:
                    a[row][col%Nc] = "v"
            elif b[row][col] != '.':
                a[row][col] = b[row][col]
    return ["".join(x) for x in a]


def step(before):
    return stepDown(stepRight(before))

assert( step(["...>>>>>..."]) == ["...>>>>.>.."] )
assert( step(["...>>>>.>.."]) == ["...>>>.>.>."] )

def pr(x):
    for q in x:
        print(q)

ex = ["..........",
      ".>v....v..",
      ".......>..",
      ".........."]

assert(
    ["..........",
     ".>........",
     "..v....v>.",
     ".........."] ==
    step(ex))

def solve_a(ex):
    count = 1
    a=ex
    b=step(ex)
    while(a!=b):
        count+=1
        a=b
        b=step(a)
    return count

assert(58 == 
       solve_a(["v...>>.vv>",
                ".vv>>.vv..",
                ">>.>v>...v",
                ">>v>>.>.v.",
                "v>v.vv.v..",
                ">.>>..v...",
                ".vv..>.>v.",
                "v.v..>>v.v",
                "....v..v.>"]))

print(solve_a(open("input").readlines()))

