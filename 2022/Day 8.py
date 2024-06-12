input = open("Day 8.txt").read()
rows = [[int(t) for t in text] for text in input.split("\n")]
height = len(rows)
width = len(rows[0])

def Part_1():
    visible = {}
    for step in [1, -1]:
        for y in range(1, height - 1):
            tallest = rows[y][0 if step == 1 else -1]
            for x in range(0, width * step, step):
                if (x in [0, -1, width - 1, -(width - 1)]): continue
                if rows[y][x] > tallest: 
                    visible[(x % width, y % height)] = 1
                    tallest = rows[y][x]
                    if (rows[y][x] == 9): break

        for x in range(1, width - 1):
            tallest = rows[0 if step == 1 else -1][x]
            for y in range(0, height * step, step):
                if (y in [0, -1, height - 1, -(height - 1)]): continue
                if rows[y][x] > tallest: 
                    visible[(x % width, y % height)] = 1
                    tallest = rows[y][x]
                    if (rows[y][x] == 9): break
    print(f"Part 1: {len(visible.keys()) + (height + width - 2) * 2}")

def Part_2():
    highest = 0
    for y in range(1, height - 1):
        for x in range(1, width - 1):
            tree = rows[y][x]
            view = 1
            for step in [1, -1]:
                dx = dy = 0
                for xx in range(x, -1 if step == -1 else width, step):
                    if (xx == x): continue
                    dx += 1
                    if (rows[y][xx] >= tree): break

                for yy in range(y, -1 if step == -1 else height, step):
                    if (yy == y): continue
                    dy += 1
                    if (rows[yy][x] >= tree): break
                view *= dx * dy
            if (view > highest): highest = view
    print(f"Part 2: {highest}")

Part_1()
Part_2()




def alt_method_1():
    visible = 0
    for y in range(1, height - 1):
        for x in range(1, width - 1):
            tree = rows[y][x]
            for step in [1, -1]:
                is_visible = True
                for xx in range(x, -1 if step == -1 else width, step):
                    if (xx == x): continue
                    if (rows[y][xx] >= tree):
                        is_visible = False
                        break
                if (is_visible):
                    visible += 1
                    break
                is_visible = True
                for yy in range(y, -1 if step == -1 else height, step):
                    if (yy == y): continue
                    if (rows[yy][x] >= tree):
                        is_visible = False
                        break
                if (is_visible):
                    visible += 1
                    break

    print(f"Part 1: {visible + (height + width - 2) * 2}")
