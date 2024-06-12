input = open("Day 24.txt").read()
lines = input.split("\n")
points = ((lines[0].index("."), 0), (lines[-1].index("."), len(lines) - 1))
blizzards = {}
ranges = (len(lines[0]) - 2, len(lines) - 2)
steps = 0

def add_pos(dict, key, value):
    if (key not in dict): dict[key] = set()
    dict[key].add(value)

for y, line in enumerate(lines):
    for x, char in enumerate(line):
        if (char in {">", "<", "v", "^"}):
            match char:
                case ">": direction = (0, 1)
                case "<": direction = (0, -1)
                case "^": direction = (1, -1)
                case "v": direction = (1, 1)
            add_pos(blizzards, y, (x, direction))

def find_blizzard(p_list):
    for dir in [1, -1]:
        for i in range(2):
            copy = list(p_list)
            copy[i] = (copy[i] + dir * steps - 1) % ranges[i] + 1
            if (copy[1] in blizzards and (copy[0], (i, -dir)) in blizzards[copy[1]]): return True
    return False

def move(start, end):
    global blizzards, steps
    initial = steps
    players = {start}
    while (end not in players):
        steps += 1
        new_players = set()
        for p in players:
            for dir in [1, -1]:
                for i in [0, 1]:
                    p_list = list(p)
                    p_list[i] += dir
                    if (p_list[1] < 0 or p_list[1] >= len(lines) or lines[p_list[1]][p_list[0]] == "#"): continue
                    if (not find_blizzard(p_list)): 
                        new_players.add(tuple(p_list))
                        if (tuple(p_list) == end): return steps - initial
            if (not find_blizzard(p)): new_players.add(p)
        players = new_players

i = 0
total = []
def get_trip(n):
    global i, total
    if (n <= len(total)): return total[n - 1]
    remaining = n - i
    for t in range(remaining):
        start = points[i % 2]
        end = points[(i + 1) % 2]
        total.append(move(start, end))
        i += 1
    return sum(total[:n])

print(f"Part 1: {get_trip(1)}")
print(f"Part 2: {get_trip(3)}")