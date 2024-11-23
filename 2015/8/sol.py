import re

sd=open("fake.txt")

def transf(s):
    return re.sub("\\\\x[0-9]{2}", "Y", s[1:-2].replace('\\"', 'X'))

def chars_in_string_data(s):
    return len(transf(s))

def of_code(s):
    return len(s)-1

s=next(sd) #""
print(s)
ans = chars_in_string_data(s)
print(ans)
assert(ans==0)
ans = code(s)
print(ans)
assert(ans==2)

s=next(sd) #"abc"
print(s)
ans = chars_in_string_data(s)
print(ans)
assert(ans==3)
ans = code(s)
print(ans)
assert(ans==5)

s=next(sd) #"abc"
print(s)
ans = chars_in_string_data(s)
print(ans)
assert(ans==3)
ans = code(s)
print(ans)
assert(ans==5)

