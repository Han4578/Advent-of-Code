from re import findall

input = open("Day 5.txt").read()
instructions = input.split("\n\n")[1].split("\n")
stacks = ["HBVWNMLP", "MQH", "NDBGFQML", "ZTFQMWG", "MTHP", "CBMJDHGT", "MNBFVR", "PLHMRGS", "PDBCN"]

def Part_1():
    for i in instructions:
        num = [int(n) for n in findall("[0-9]+", i)]
        count = num[0]
        from_stack = num[1] - 1
        to_stack = num[2] - 1
        crates = stacks[from_stack]
        stacks[from_stack] = crates[:-count]
        stacks[to_stack] += crates[:-count - 1:-1]

    final = "".join([t[-1] for t in stacks])
    print(f"Part 1: {final}")

def Part_2():
    for i in instructions:
        num = [int(n) for n in findall("[0-9]+", i)]
        count = num[0]
        from_stack = num[1] - 1
        to_stack = num[2] - 1
        crates = stacks[from_stack]
        stacks[from_stack] = crates[:-count]
        stacks[to_stack] += crates[-count:]

    final = "".join([t[-1] for t in stacks])
    print(f"Part 2: {final}")

Part_1()
Part_2()