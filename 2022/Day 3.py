input = open("Day 3.txt", "r").read()
rucksacks = input.split("\n")

def part_1():
    total = 0

    for sack in rucksacks:
        middle = int(len(sack) / 2)
        c1 = set(sack[0:middle])
        c2 = set(sack[middle:])
        ctype = ""
        for x in c1:
            if (x in c2):
                ctype = x
                break
        n = ord(ctype)
        n -= 96 if n >= 97 else 38
        total += n

    print(f"Part 1: {total}")

def part_2():
    total = 0
    for i in range(0, len(rucksacks) - 1, 3):
        sacks = rucksacks[i: i + 3]
        c1 = set(sacks[0])
        c2 = set(sacks[1])
        c3 = set(sacks[2])
        ctype = ""
        for x in c1:
            if (x in c2 and x in c3):
                ctype = x
                break
        n = ord(ctype)
        n -= 96 if n >= 97 else 38
        total += n

    print(f"Part 2: {total}")

part_1()
part_2()