input = open("Day 14.txt").read()
lines = input.split("\n")
obstacles = {}
total = 0

def add_obstacle(x, y):
    if (y not in obstacles): obstacles[y] = []
    obstacles[y].append(x)
    
for line in lines:
    line = list(map(lambda l: [int(n) for n in l.split(",")] , line.split(" -> ")))
    current = line.pop(0)
    for point in line:
        if (point[0] == current[0]):
            for y in range(min(point[1], current[1]), max(point[1], current[1]) + 1): add_obstacle(point[0], y)
        else: 
            for x in range(min(point[0], current[0]), max(point[0], current[0]) + 1): add_obstacle(x, point[1])
        current = point
lowest = max(obstacles.keys())

def drop_sand():
    global total
    x, y = 500, 0
    total += 1
    while (True):
        if (y < lowest + 1):
            if (y + 1 not in obstacles or x not in obstacles[y + 1]): pass
            elif (x - 1 not in obstacles[y + 1]): x -= 1
            elif (x + 1 not in obstacles[y + 1]): x += 1
            else: 
                add_obstacle(x, y)
                return (x, y)
        else: 
            add_obstacle(x, y)
            return (x, y)
        y += 1

def Part_1():
    while (drop_sand()[1] < lowest): pass
    print(f"Part 1: {total - 1}")

def Part_2():
    while (drop_sand() != (500, 0)): pass
    print(f"Part 2: {total}")

Part_1()
Part_2()