# ss is splitted s

def target(s): return s.split(" -> ")[1]

def source(s):
    if command(s)=="NOT":
        return s.split()[1]
    else:
        return s.split()[0]

def command(s):
    s=s.split()
    if s[0]=="NOT":
        return "NOT"
    else:
        return s[1]

def args(s): return s.split()[2]

assert(target("bn RSHIFT 2 -> bo") == "bo")
assert(source("bn RSHIFT 2 -> bo") == "bn")
assert(command("bn RSHIFT 2 -> bo") == "RSHIFT")
assert(args("bn RSHIFT 2 -> bo") == "2")
assert("NOT" == command("NOT jh -> ji"))
assert("->" == command("lx -> a"))
assert("jh" == source("NOT jh -> ji"))


def get(d, pos):
    try:
        return int(pos)
    except:
        return int(d[pos])

def process(d,s):
    c = command(s)
    a = get(d, source(s))
    if c=='->':
        return get(d, a)
    elif c=="NOT":
        return 65535-get(d, a)
    else:
        b = get(d, args(s))
        if c == "AND":
            return a & b
        elif c == "OR":
            return a | b
        elif c == "LSHIFT":
            return a << b
        elif c == "RSHIFT":
            return a >> b

def solve(cmds, d = None):
    if d is None:
        d = dict()
    old_len = -1
    while old_len < len(d):
        old_len = len(d)
        for s in cmds:
            try:
                t = target(s)
                if not t in d.keys():
                    d[t] = int(process(d, s))
            except:
                pass
    return d

assert(
    {
        'd': 72,
        'e': 507,
        'f': 492,
        'g': 114,
        'h': 65412,
        'i': 65079,
        'x': 123,
        'y': 456 } == solve(["123 -> x", "456 -> y",
                           "x AND y -> d",
                           "x OR y -> e",
                           "x LSHIFT 2 -> f",
                           "y RSHIFT 2 -> g",
                           "NOT x -> h",
                           "NOT y -> i"
                           ]))


data = list(x.strip() for x in open("input").readlines())
first = solve(data)
assert(first['a']==46065)
print(first['a'])
print(first['b'])


print(solve(data, {'b':46065})['a'])






