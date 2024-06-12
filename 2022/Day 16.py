from re import findall

input = open("Day 16.txt").read()
lines = input.split("\n")
info = [findall(r"[A-Z]{2}|\d+", l) for l in lines]
tunnels = {i[0] : { "id": i[0], "flow": int(i[1]), "connects": i[2:]} for i in info}

def move(current_tunnel_id, previous, time):
    time += 1
    current_tunnel = tunnels[current_tunnel_id]
    if (current_tunnel["flow"] > 0 or len(current_tunnel["connects"]) > 2): return (current_tunnel_id, time)
    else:
        for id in current_tunnel["connects"]:
            if (id != previous): return move(id, current_tunnel_id, time)

def dijkstra(key):
    distance, current_step, next_step = {key: 0}, key, []
    while True:
        tunnel = tunnels[current_step]
        for next in tunnel["connects"]:
            (next, d) = move(next, current_step, 0)
            if (next not in distance): next_step.append((next, d + distance[current_step]))
        next_step = list(filter(lambda x: x[0] not in distance, next_step))
        if (len(next_step) == 0): break
        shortest = min(next_step, key=lambda x: x[1])
        current_step = shortest[0]
        distance[current_step] = shortest[1]
    return distance

def test_path(key, history, time, total):
    current = tunnels[key]
    h = history.copy() + [key]
    time -= current["short"][h[-2]] + 1
    if (time <= 0): return total
    total += time * current["flow"]
    highest = total
    for k in current["short"].keys():
        if (k not in h and tunnels[k]["flow"] > 0): highest = max(test_path(k, h, time, total), highest)
    return highest

def test_path_2(key, history, time, total, possibilities):
    current = tunnels[key]
    h = history.copy() + [key]
    time -= current["short"][h[-2]] + 1
    if (time <= 0): return add_possibility(possibilities, history[1:], total)
    total += time * current["flow"]
    short = current["short"]
    for k in short.keys():
        if (k not in h and tunnels[k]["flow"] > 0 and time - short[k] > 0): test_path_2(k, h, time, total, possibilities)
    if (all([kk in h or time - short[kk] <= 0 for kk in short.keys()])): add_possibility(possibilities, h[1:], total)

def add_possibility(possibilities, history, total):
    ordered = ",".join(sorted(history)) 
    if (ordered in possibilities): possibilities[ordered] = max(possibilities[ordered], total)
    else: possibilities[ordered] = total

def Part_1():
    highest = 0
    for path in tunnels["AA"]["short"].keys():
        if (tunnels[path]["flow"] > 0): highest = max(test_path(path, ["AA"], 30, 0), highest)

    print(f"Part 1: {highest}")

def Part_2():
    possibilities = {}
    for path in tunnels["AA"]["short"].keys():
        if (tunnels[path]["flow"] > 0): test_path_2(path, ["AA"], 26, 0, possibilities)

    high_to_low = sorted(possibilities.items(), key=lambda x: x[1], reverse=True)
    for i in range(0, len(high_to_low) - 1):
        c1 = high_to_low[i]
        cl1 = c1[0].split(",")
        for ii in range(i + 1, len(high_to_low)):
            c2 = high_to_low[ii]
            cl2 = c2[0].split(",")
            if (any([v in cl2 for v in cl1])): continue
            print(f"Part 2: {c1[1] + c2[1]}")
            return

for key, stuff in tunnels.items():
    stuff["short"] = dijkstra(key) if (stuff["flow"] > 0 or len(stuff["connects"]) > 2) else {}

Part_1()
Part_2()