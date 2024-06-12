input = open("Day 4.txt").read()
pairs = input.split("\n")

def Part_1():
    total = 0

    for pair in pairs:
        pair = pair.split(",")
        p1 = [int(n) for n in pair[0].split("-")]
        p2 = [int(n) for n in pair[1].split("-")]
        if ((p1[0] <= p2[0] and p1[1] >= p2[1]) or (p2[0] <= p1[0] and p2[1] >= p1[1])): total += 1

    print(f"Part 1: {total}")

def Part_2():
    total = 0

    for pair in pairs:
        pair = pair.split(",")
        p1 = [int(n) for n in pair[0].split("-")]
        p2 = [int(n) for n in pair[1].split("-")]
        if (not (p1[0] > p2[1] or p1[1] < p2[0])): total += 1

    print(f"Part 2: {total}")

Part_1()
Part_2()