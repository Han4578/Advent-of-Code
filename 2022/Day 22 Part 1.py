from re import search, findall

input = open("Day 22.txt").read()
stuff = input.split("\n\n")
board = stuff[0].split("\n")
instructions = findall(r"(\d+|L|R)", stuff[1])
horizontal = {}
vertical = {}

for y, line in enumerate(board):
    start = search(r"[.#]", line).span()[0] + 1
    end = len(line)
    horizontal[y + 1] = (start, end)

for x in range(len(max(board, key=len))):
    line = "".join(map(lambda b: b[x] if (len(b) - 1 >= x) else " ", board)).rstrip()
    start = search(r"[.#]", line).span()[0] + 1
    end = len(line)
    vertical[x + 1] = (start, end)

def warp(tup, val):
    if (val < tup[0] or val > tup[1]):
        r = tup[1] - tup[0] + 1
        val = (val - tup[0]) % r + tup[0]
    return val

def move_x(x, y, dir, steps):
    ends = horizontal[y]
    for i in range(steps):
        temp_x = warp(ends, x + dir)
        if (board[y - 1][temp_x - 1] == "#"): break
        x = temp_x
    return x

def move_y(x, y, dir, steps):
    ends = vertical[x]
    for i in range(steps):
        temp_y = warp(ends, y + dir)
        if (board[temp_y - 1][x - 1] == "#"): break
        y = temp_y
    return y

def Part_1():
    dir = 0
    x = horizontal[1][0]
    y = 1
    for ins in instructions:
        match ins:
            case "L": dir = (dir - 1) % 4
            case "R": dir = (dir + 1) % 4
            case _:
                num = int(ins)
                match dir:
                    case 0: x = move_x(x, y, 1, num)
                    case 1: y = move_y(x, y, 1, num)
                    case 2: x = move_x(x, y, -1, num)
                    case 3: y = move_y(x, y, -1, num)
    print(f"Part 1: {1000 * y + 4 * x + dir}")

Part_1()