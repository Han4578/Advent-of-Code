input = open("Day 23.txt").read()
lines = input.split("\n")
elves = {}
positions = {}

def add_position(dict, key, value):
    if (key not in dict): dict[key] = set()
    dict[key].add(value)

def move(n = 10, endless = False):
    elves.clear()
    positions.clear()
    for y, line in enumerate(lines):
        for x, elf in enumerate(line):
            if (elf == "#"): add_position(elves, y, x)
    adjacent = [(0, -1), (-1, -1), (1, -1), (0, 1), (-1, 1), (1, 1), (-1, 0), (-1, 1), (-1, -1), (1, 0), (1, 1), (1, -1)]
    considerations = [((0, -1), 0, 1, 2), ((0, 1), 3, 4, 5), ((-1, 0), 6, 7, 8), ((1, 0), 9, 10, 11)]
    q = 0
    while (q < n or endless):
        for y, x_list in elves.items():
            for x in x_list:
                if (all([a[1] + y not in elves or a[0] + x not in elves[a[1] + y] for a in adjacent])): continue
                for consideration in considerations:
                    step = consideration[0]
                    if (all([adjacent[c][1] + y not in elves or adjacent[c][0] + x not in elves[adjacent[c][1] + y] for c in consideration[1:]])):
                        add_position(positions, (step[0] + x, step[1] + y), (x, y))
                        break
        if (positions.__len__() == 0 and endless): return q + 1
        for new_pos, elf in positions.items():
            if (len(elf) > 1): continue
            elf = elf.pop()
            elves[elf[1]].remove(elf[0])
            add_position(elves, new_pos[1], new_pos[0])
        considerations.append(considerations.pop(0))
        positions.clear()
        q += 1

    min_x = min(min(elves.values(), key=lambda e: min(e) if (len(e) > 0) else 0))
    max_x = max(max(elves.values(), key=lambda e: max(e) if (len(e) > 0) else 0))
    min_y = min(elves.keys(), key=lambda y: y if len(elves[y]) > 0 else 0)
    max_y = max(elves.keys(), key=lambda y: y if len(elves[y]) > 0 else 0)
    return (max_x - min_x + 1) * (max_y - min_y + 1) - sum(len(e) for e in elves.values())

def Part_1():
    print(f"Part 1: {move(10)}")
def Part_2():
    print(f"Part 2: {move(endless=True)}")

Part_1()
Part_2()