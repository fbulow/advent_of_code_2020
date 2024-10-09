import re

def has_double(s):
    for a,b in zip(s[:-1], s[1:]):
        if a==b:
            return True
    return False

def nice(s):
    for x in "ab cd pq xy".split():
        if x in s:
            return False
    try:
        vowels = (x for x in s if x in "aeiou")
        next(vowels)
        next(vowels)
        next(vowels)
    except:
        return False

    if not has_double(s):
        return False
    
    return True

print(sum(1 for s in open("input") if nice(s)))

def all_pairs(s):
    return set((a+b for a,b in zip(s[:-1],s[1:])))


def two_none_overlapping(s, pair):
    one = s.find(pair)
    if one == -1:
        return False
    
    return s[(one+2):].find(pair) != -1

def first_rule(s):
    return any( two_none_overlapping(s, pair) for pair in all_pairs(s) )
        

def second_rule(s):
    for a, b in zip(s[:-2], s[2:]):
        if a==b:
            return True
    return False

def nice_b(s):
    return first_rule(s) and second_rule(s)

print(sum(1 for s in open("input") if nice_b(s)))
