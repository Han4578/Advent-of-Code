input = open("Day 6.txt").read()

def Part_1():
    final = ""
    length = 4
    for i in range(0, len(input) - 1):
        if (len(set(input[i: i + length])) == length):
            final = i + length
            break

    print(f"Part 1: {final}")

def Part_2():
    final = ""
    length = 14
    for i in range(0, len(input) - 1):
        if (len(set(input[i: i + length])) ==  length):
            final = i + length
            break

    print(f"Part 2: {final}")

Part_1()
Part_2()