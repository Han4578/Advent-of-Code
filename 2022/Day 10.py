from re import search

input = open("Day 10.txt").read()
commands = input.split("\n")

def Part_1():
    total = i = add_next = 0
    value = cycle = 1
    while (i < len(commands)):
        if ((cycle - 20) % 40 == 0): total += cycle * value
        if (add_next != 0):
            value += add_next
            add_next = 0
            i += 1
        else:
            command = commands[i]
            if (command == "noop"): i += 1
            else: add_next = int(search("-*[0-9]+", command).group())
        cycle += 1

    print(f"Part 1: {total}")

def Part_2():
    i = add_next = 0
    value = 1
    cycle = 0
    line = ""
    while (i < len(commands)):
        line += "#" if (abs(value - cycle % 40) <= 1) else "."
        if (add_next != 0):
            value += add_next
            add_next = 0
            i += 1
        else:
            command = commands[i]
            if (command == "noop"): i += 1
            else: add_next = int(search("-*[0-9]+", command).group())
        cycle += 1
        if (cycle % 40 == 0): 
            print(line)
            line = ""

Part_1()
Part_2()