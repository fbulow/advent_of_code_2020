#!/usr/bin/python3

data =  open("input").readlines()

def count(data, pos, val):
    return sum(int(x[pos]==val) for x in data)


def gamma(data):
    ret=""
    for col in range(len(data[0])-1):
        zero = count(data, col, '0')
        one = count(data, col, '1')
        if zero>=one:
           ret+='0'
        else:
           ret+='1'
    return ret

def epsilon(data):
    ret = ''
    for x in gamma(data):
        if x=='1':
            ret+='0'
        elif x=='0':
            ret+='1'
    return ret
        
sol_a = int(gamma(data),2)*int(epsilon(data),2)
assert(693486 == sol_a)
print("a: ", sol_a)


def datafilter(data, bit_criteria, col=0):
    if len(data)<=1:
        return data[0]
    else:
        bc = bit_criteria(data, col)
        return datafilter([x for x in data if x[col]==bc],
                          bit_criteria,
                          col+1)
    
def bc_oxygen(data, pos):
    if count(data, pos, '1') >= count(data, pos, '0'):
        return '1'
    else:
        return '0'

def bc_scrub(data, pos):
    if count(data, pos, '1') >= count(data, pos, '0'):
        return '0'
    else:
        return '1'
    
        
    

    
example =    ["00100",
     "11110",
     "10110",
     "10111",
     "10101",
     "01111",
     "00111",
     "11100",
     "10000",
     "11001",
     "00010",
     "01010"],

    
sol_b= int(datafilter(data, bc_oxygen),2)*int(datafilter(data, bc_scrub),2)

print("b: ", sol_b)
assert(sol_b>688864)




