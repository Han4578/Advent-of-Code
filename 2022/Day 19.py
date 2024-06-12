from re import findall
from math import ceil

input = open("Day 19.txt").read()
lines = input.split("\n")
blueprints_list = [[list(map(lambda x: x.split(" "), filter(lambda x: x != "", f[0::3]))) for f in findall(r"costs (\d+ (ore|clay|obsidian))( and (\d+ (ore|clay|obsidian)))?", l)] for l in lines]
blueprints = []
highest = 0

for l in blueprints_list:
    blueprint = {"inventory": (0, 0, 0), "robots": (1, 0, 0), "costs": [], "time": 0, "geodes": 0}
    for cost in l:
        array = [0, 0, 0]
        for c in cost:
            match c[1]:
                case "ore": array[0] = int(c[0])
                case "clay": array[1] = int(c[0])
                case "obsidian": array[2] = int(c[0])
        blueprint["costs"].append(tuple(array))
    blueprint["costs"] = tuple(blueprint["costs"])
    blueprint["max-cost"] = tuple(max(map(lambda c: c[i], blueprint["costs"])) for i in range(3))
    blueprints.append(blueprint)

def buy(p, item, time):
    global highest
    cost = p["costs"][item]
    if (any([cost[i] > 0 and p["robots"][i] == 0 for i in range(3)])): return
    min_time = max([0] + [ceil((cost[i] - p["inventory"][i]) / p["robots"][i]) for i in range(3) if p["robots"][i] > 0]) + 1
    if ((time - p["time"]) < min_time): return
    p["time"] += min_time
    p["inventory"] = tuple(p["inventory"][i] + p["robots"][i] * min_time - cost[i] for i in range(3))
    if (item < 3): p["robots"] = tuple(r + (1 if (i == item) else 0) for i, r in enumerate(p["robots"]))
    else: p["geodes"] += time - p["time"]
    highest = max(highest, p["geodes"])
    if (sum(i + 1 for i in range(time - p["time"])) + p["geodes"] <= highest): return
    for i in range(4):
        if (i < 3 and (p["robots"][i] * (time - p["time"]) + p["inventory"][i] >= p["max-cost"][i] * (time - p["time"]) or time - p["time"] <= 2)): continue
        buy(p.copy(), i, time)

def Part_1():
    global highest
    total = 0
    for id, blueprint in enumerate(blueprints):
        highest = 0
        for i in range(4):
            buy(blueprint.copy(), i, 24)
        total += (id + 1) * highest
    print(f"Part 1: {total}")

def Part_2():
    global highest
    total = 1
    for blueprint in blueprints[0:3]:
        highest = 0
        for i in range(4):
            buy(blueprint.copy(), i, 32)
        total *= highest
    print(f"Part 2: {total}")

Part_1()
Part_2()