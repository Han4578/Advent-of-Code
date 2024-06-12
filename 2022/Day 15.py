from re import findall

input = open("Day 15.txt").read()
lines = input.split("\n")
coords = [[int(n) for n in findall(r"-*\d+", line)] for line in lines]
    
def get_range(target):
    ranges = []
    blockage = {}
    for c in coords:
        if (c[1] == target): blockage[(c[0], c[1])] = 1
        if (c[3] == target): blockage[(c[2], c[3])] = 1
        max_distance = abs(c[3] - c[1]) + abs(c[2] - c[0])
        radius = max_distance - abs(target - c[1])
        if (radius >= 0): ranges.append((c[0] - radius, c[0] + radius))

    return (sorted(ranges, key= lambda x: x[0]), blockage.keys())

def Part_1():
    (ranges, blockage) = get_range(2000000)
    point = ranges[0][0]
    total = 1
    while (len(ranges) > 0):
        r = ranges.pop(0)
        if point < r[0]: point = r[0]
        if (point >= r[0] and point < r[1]):
            total += r[1] - point
            point = r[1]
    print(f"Part 1: {total - len(blockage)}")

def Part_2():
    size = 4000000
    for y in range(size):
        ranges = get_range(y)[0]
        point = 0
        while (point <= size):
            r = ranges.pop(0)
            if point < r[0]: 
                print(f"Part 2: {point * 4000000 + y}")
                exit()
            if (point >= r[0] and point < r[1]):
                point = r[1] + 1

Part_1()
Part_2() #very slow, 30 secs


def math_2(): #part 2 but without brute force and much faster
    sensors = []
    intersections = {}
    for c in coords:
        sensors.append([(c[0], c[1]), abs(c[3] - c[1]) + abs(c[2] - c[0]) + 1])
    for i in range(0, len(sensors) - 1):
        (x1, y1), d1 = sensors[i]
        for ii in range(i + 1, len(sensors)):
            (x2, y2), d2 = sensors[ii]
            for m1 in [1, -1]:
                for m2 in [1, -1]:
                    if (m1 == m2): continue
                    for dir1 in [1, -1]:
                        for dir2 in [1, -1]:
                            c1 = y1 - x1 * m1 - d1 * dir1
                            c2 = y2 - x2 * m2 - d2 * dir2
                            x = int((c2 - c1) / (m1 - m2))
                            y = int(x * m1 + c1)
                            if (x > 0 and x <= 4e6 and y > 0 and y <= 4e6):
                                intersections[(x, y)] = intersections[(x, y)] + 1 if ((x, y) in intersections) else 1
    for (x1, y1), p in filter(lambda item: item[1] > 3 , intersections.items()):
        if (all([abs(x1 - x2) + abs(y1 - y2) >= d for (x2, y2), d in sensors])):
            print(f"Part 2: {x1 * 4000000 + y1}")
            return
math_2()