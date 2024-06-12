input = open("Day 20.txt").read()
order = [(i, int(n)) for i, n in enumerate(input.split("\n"))]

def mix(n = 1, key = 1):
    arrangement = order.copy()
    zero = list(filter(lambda n: n[1] == 0, arrangement))[0]
    for i in range(n):
        for o in order:
            current = arrangement.index(o)
            new = (current + o[1] * key) % (len(arrangement) - 1)
            arrangement.insert(new, arrangement.pop(current))
    z = arrangement.index(zero)
    return sum(arrangement[(z + i) % (len(arrangement))][1] for i in range(1000, 3001, 1000)) * key

def Part_1():
    print(f"Part 1: { mix()}")

def Part_2():
    key = 811589153
    print(f"Part 2: {mix(10, key)}")

Part_1()
Part_2()