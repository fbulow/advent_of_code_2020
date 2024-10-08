from hashlib import md5

input = "iwrupvqb"

i=0
while '00000' != md5((input+str(i)).encode()).digest().hex()[:5]:
    i+=1
print(i)

while '000000' != md5((input+str(i)).encode()).digest().hex()[:6]:
    i+=1
print(i)

