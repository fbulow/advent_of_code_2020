

def is_simple_number(active_segments):
    a = active_segments
    return (a==2) or (a==4) or (a==3) or (a==7) 

def simple_count(line= "fdaebc egc gc bgefc ecbagd becfa fagc afgbec gdcbfae bgdef | cgfa gcebad ebcadfg cefgbad"):
    return sum(int(is_simple_number(n)) for n in (len(x) for x in line.split("|")[1].strip().split()))


