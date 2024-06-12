input = open("Day 12.txt").read()
lines = input.split("\n")
start = (input.index("S") % (len(lines[0]) + 1), int(input.index("S") / len(lines[0])), 0)
end = (input.index("E") % (len(lines[0]) + 1), int(input.index("E") / len(lines[0])), 27)
map = [[ord(t) - 96 if t not in ["S", "E"] else 0 if t == "S" else 27 for t in line] for line in lines]

def trek(start_point, min, max, final_altitude):
    next_step = []
    current_steps = []
    history = {}
    steps = 0
    current_steps = [start_point]
    history = {start_point: 1}
    while len(current_steps) > 0:
        steps += 1
        while (len(current_steps) > 0):
            x, y, altitude = current_steps.pop()
            stuff = []
            for s in [1, -1]:
                if (x + s >= 0 and x + s < len(map[0])): stuff.append((x + s, y, map[y][x + s]))
                if (y + s >= 0 and y + s < len(map)): stuff.append((x, y + s, map[y + s][x]))
            for x, y, step in stuff:
                if ((x, y) not in history and step - altitude >= min and step - altitude <= max):
                    if (step == final_altitude): return steps
                    history[(x, y)] = 1
                    next_step.append((x, y, step))
        current_steps = next_step
        next_step = []

def Part_1():
    steps = trek(start, -float("inf"), 1, 27)
    print(f"Part 1: {steps}")
    

def Part_2():
    steps = trek(end, -1, float("inf"), 1)
    print(f"Part 2: {steps}")

Part_1()
Part_2()