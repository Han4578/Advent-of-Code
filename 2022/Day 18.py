input = open("Day 18.txt").read()
lines = input.split("\n")
cubes = [eval(l) for l in lines]

def Part_1():
    total = 0
    for c in cubes:
        for dir in [1, -1]:
            for i in range(3):
                copy = list(c)
                copy[i] += dir
                if (tuple(copy) not in cubes): total += 1
    print(f"Part 1: {total}")

def Part_2():
    total = 0
    x_range = (min(cubes, key=lambda x: x[0])[0] - 1, max(cubes, key=lambda x: x[0])[0] + 1)
    y_range = (min(cubes, key=lambda x: x[1])[1] - 1, max(cubes, key=lambda x: x[1])[1] + 1)
    z_range = (min(cubes, key=lambda x: x[2])[2] - 1, max(cubes, key=lambda x: x[2])[2] + 1)
    ranges = (x_range, y_range, z_range)
    history = []
    current_step = [[x_range[0], y_range[0], z_range[0]]]

    while len(current_step) > 0:
        next = []
        while len(current_step) > 0:
            current = current_step.pop(0)
            for dir in [1, -1]:
                for i in range(3):
                    copy = list(current)
                    copy[i] += dir
                    tuple_copy = tuple(copy)
                    if (copy[i] < ranges[i][0] or copy[i] > ranges[i][1]): continue
                    if (tuple_copy in cubes): total += 1
                    elif (tuple_copy not in history and tuple_copy not in next): next.append(tuple_copy)
            history.append(tuple(current))
        current_step = next
    print(f"Part 2: {total}")

Part_1()
Part_2()