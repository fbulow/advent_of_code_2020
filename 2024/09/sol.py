from unittest import TestCase, main
import re
import pdb
import sys

sys.setrecursionlimit(100000)


self = TestCase

def puzzle_input(filename="input"):
    with open(filename,'r') as f:
        return [x.strip() for x in f.readlines()]

def asString(values):
    def asChar(val):
        if val is None:
            return '.'
        else:
            return str(val)
    return "".join(asChar(v) for v in values)
    
def expand(line):
    active = True
    count = 0
    for char in line:
        for _ in range(int(char)):
            if active:
                yield count
            else:
                yield None
        if active:
            active = False
        else:
            active = True
            count+=1

def compress(values):
    v = list(values)
    i,j = 0, (len(v)-1)
    while i<=j:
        if v[i] is None:
            if not v[j] is None:
                yield v[j]
                i = i+1
            j=j-1
        else:
            yield v[i]
            i=i+1
    while j<(len(v)-1):
        j+=1
        yield None

def group(values):
    prev  = None #First value is never None
    count = 0
    for v in values:
        if v!=prev:
            if count>0:
                if prev is None:
                    yield count
                else:
                    yield(count, prev)
            count = 1
            prev  = v
        else:
            count+=1
    if count>0:
        if prev is None:
            yield count
        else:
            yield(count, prev)


def is_space(element):
    return isinstance(element, int)

def file_pack(elements, ret=()):
    elements=list(elements)
    ret = list(ret)

    if len(elements)==0:
        return ret

    if is_space(elements[-1]):
        ret = [elements.pop()] + ret
    else:
        count, file_id = elements.pop()
        try:
            i,nzeros = next((i,nzeros) for i, nzeros in enumerate(elements) \
                            if isinstance(nzeros, int) and nzeros >= count)
            elements[i:i+1] = (count, file_id), nzeros-count
            ret = [count] + ret
        except StopIteration:
            ret = [(count, file_id)] + ret
    return file_pack(elements, ret)

def ungroup(data):
    for d in data:
        if is_space(d):
            for _ in range(d):
                yield None
        else:
            count, file_id = d

            for _ in range(count):
                yield file_id
            

def solA(lines):
    return sum((i*v for i,v in enumerate(compress(expand(lines[0]))) if not v is None))

def solB(lines):
    return sum((i*v for i,v in enumerate(ungroup(file_pack(group(expand(lines[0]))))) if not v is None))


class Test_(TestCase):
    def test_solB(self):
        self.assertEqual(
            2858,
            solB(["2333133121414131402"]))
    def test_file_pack(self):
        self.assertEqual(
            [(1, 0), (5,2), 0, (3, 1)],
            file_pack([(1, 0), 5, (3, 1), (5,2)]))
            
        
    def test_file_pack(self):
        self.assertEqual(
            "00992111777.44.333....5555.6666.....8888..",
            asString(ungroup(file_pack(group(expand("2333133121414131402"))))))
            
    def test_group_no_space_at_end(self):
        self.assertEqual(
            [(2,0), 3, (3,1)],
            list(group(expand("2330"))))


    def test_group(self):
        self.assertEqual(
            [(2,0), 3, (3,1), 2],
            list(group(expand("2332"))))
            
    def test_solA(self):
        self.assertEqual(
            1928,
            solA(["2333133121414131402"]))

    def test_compress(self):
        self.assertEqual(
            "0099811188827773336446555566..............",
            asString(compress(expand("2333133121414131402"))))

    def test_expand(self):
        self.assertEqual(
            '00...111...2...333.44.5555.6666.777.888899',
            asString(expand("2333133121414131402")))

print(f"A: {solA(puzzle_input('input'))}")

ret_b = solB(puzzle_input('input'))
assert ret_b > 6316578423261
print(f"B: {ret_b}")
#main()
