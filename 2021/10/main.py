def score(line):
    stack = []
    for x in line:
        if x in "({[<":
            stack+=x
        else:
            if not x == {'(': ')', '[': ']', '{': '}', '<': '>'}[stack.pop()]:
                return {')': 3,
                        ']': 57,
                        '}': 1197,
                        '>': 25137}[x]
    return 0

print("a:", sum(score(x.strip()) for x in open('input').readlines()))

def completion(line):
    stack = []
    for x in line:
        if x in "({[<":
            stack+=x
        else:
            assert(x == {'(': ')', '[': ']', '{': '}', '<': '>'}[stack.pop()])
    return [{'(': ')', '[': ']', '{': '}', '<': '>'}[x] for x in reversed(stack)]
            
def score_b(comp):
    ret = 0;
    for x in comp:
        ret*=5
        ret+={')': 1,
              ']': 2,
              '}': 3,
              '>': 4}[x]
    return ret

scores = [score_b(completion(x)) for x in (x.strip() for x in open('input').readlines()) if score(x)==0]

scores.sort()

print("b: ", scores[len(scores)//2])
