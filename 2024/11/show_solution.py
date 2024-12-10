import sol

print("======= Solutions start =======")
try:
    ret_a = sol.solA(sol.puzzle_input('input'))
    if(ret_a is None):
        msg="(wrong)"
    print(f"A: {ret_a} {msg}")
    msg = ""

    ret_b = sol.solB(sol.puzzle_input('input'))
    if(ret_b is None):
        msg="(wrong)"
    print(f"B: {ret_b} {msg}")
except AttributeError:
    pass
print("======= Solutions end   =======")

