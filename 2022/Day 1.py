input = open("Day 1.txt", "r").read()
elves = input.split("\n\n")

def part_1():
    highest = 0

    for elf in elves:
        food = elf.split("\n")
        cals = [int(c) for c in food]
        total = sum(cals)
        if (total > highest): highest = total

    print(f"Part 1: {total}")

def part_2():
    highest = [0, 0, 0]

    for elf in elves:
        food = elf.split("\n")
        cals = [int(c) for c in food]
        total = sum(cals)
        i = 0
        for n in highest:
            if (total > n):
                highest.insert(i, total)
                highest = highest[0:3]
                break
            i += 1
    print(f"Part 2: {sum(highest)}")

part_1()
part_2()

# input = open("Day 1.txt", "r").read()
# elves = input.split("\n\n")
# foods = []
# def get_highest(n):
#     global foods
#     if (len(foods) == 0): 
#         foods = [sum(int(c) for c in elf.split("\n")) for elf in elves]
#         foods.sort(reverse=True)
#     return sum(foods[:n])
#
# print(f"Part 1: {get_highest(1)}")
# print(f"Part 2: {get_highest(3)}")