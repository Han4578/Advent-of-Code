from re import findall, search
from math import sqrt

input = open("Day 22.txt").read()
stuff = input.split("\n\n")
board = stuff[0].split("\n")
instructions = findall(r"(\d+|L|R)", stuff[1])
width = int(sqrt(sum(len(list(filter(lambda c: c != " ", l))) for l in board) / 6))
references = [((4, None), (6, None), (2, None), (5, None)), ((1, None), (6, None), (3, None), (5, None)), ((2, None), (6, None), (4, None), (5, None)), ((3, None), (6, None), (1, None), (5, None)), ((4, None), (1, None), (2, None), (3, None)), ((4, None), (3, None), (2, None), (1, None))]
faces = {}

def fill_coords(x, y, face, previous_dir = None, dir = None, previous = None):
    if (face in faces): return
    f = {"id": face, "x": x + 1, "y": y + 1}
    layout = []
    for i in range(width):
        layout.append(board[y + i][x: x + width])
    f["layout"] = layout
    ref = list(references[face - 1])

    if (previous_dir != None):
        while (ref[dir][0] != previous):
            ref.append(ref.pop(0))
        ref[dir] = (ref[dir][0], previous_dir)

    f["surrounding"] = tuple(ref)
    faces[face] = f
    if (len(board[y]) >= x + width + 1 and board[y][x + width] != " "): fill_coords(x + width, y, ref[1][0], 1, 3, face) # your 3 is connected to my 1
    if (x - width >= 0 and board[y][x - width] != " "): fill_coords(x - width, y, ref[3][0], 3, 1, face) # your 1 is connected to my 3
    if (len(board) >= y + width + 1 and len(board[y + width]) >= x + 1 and board[y + width][x] != " "): fill_coords(x, y + width, ref[2][0], 2, 0, face) # your 0 is connected to my 2
    if (y - width >= 0 and len(board[y - width]) >= x + 1 and board[y - width][x] != " "): fill_coords(x, y - width, ref[0][0], 0, 2, face) # your 2 is connected to my 0

def get_entry(face, previous_face, previous_exit):
    surrounding = faces[face]["surrounding"]
    entry = list(filter(lambda e: e[0] == previous_face, surrounding))[0]
    i = surrounding.index(entry)
    if (surrounding[i][1] == None): 
        surrounding_list = list(surrounding)
        surrounding_list[i] = (surrounding[i][0], previous_exit)
        faces[face]["surrounding"] = tuple(surrounding_list)
    return i
    
def convert(exit, coords, previous_exit):
    face = faces[exit[0]]
    new_coords = [c + 1 - (width + 1) / 2 for c in coords]
    for i in range((exit[1] - previous_exit) % 4):
        new_coords.reverse()
        new_coords[0] *= -1
    new_coords = [int(c - 1 + (width + 1) / 2) for c in new_coords]
    new_coords[exit[1] % 2] = width - 1 - new_coords[exit[1] % 2]
    clear = face["layout"][new_coords[1]][new_coords[0]] == "."
    return new_coords, clear

def Part_2():
    x = search(r"(\.|#)", board[0]).span()[0]
    fill_coords(x, 0, 1)
    for f in faces.values(): 
        surrounding = list(f["surrounding"])
        for i, s in enumerate(surrounding):
            if (s[1] != None): continue
            entry = get_entry(s[0], f["id"], i)
            surrounding[i] = (surrounding[i][0], entry)
        f["surrounding"] = tuple(surrounding)
    current_face = faces[1]
    layout = current_face["layout"]
    coords = [0, 0]
    direction = (0, 1)
    for ins in instructions:
        match ins:
            case "L": direction = ((direction[0] + 1) % 2, direction[1] * (1 if ((direction[0] + 1) % 2 == 0) else -1))
            case "R": direction = ((direction[0] + 1) % 2, direction[1] * (1 if ((direction[0] + 1) % 2 == 1) else -1))
            case _:
                num = int(ins)
                for n in range(num):
                    coords[direction[0]] += direction[1]
                    if (coords[0] >= width or coords[0] < 0 or coords[1] >= width or coords[1] < 0):
                        e = None
                        if (coords[1] < 0): e = 0
                        elif (coords[0] >= width): e = 1
                        elif (coords[1] >= width): e = 2
                        elif (coords[0] < 0): e = 3
                        coords[direction[0]] -= direction[1]
                        exit = current_face["surrounding"][e]
                        new_coords, clear = convert(exit, coords, e)
                        
                        if (clear):
                            coords = new_coords
                            current_face = faces[exit[0]]
                            layout = current_face["layout"]
                            for i in range((e + exit[1]) % 4 + (2 if e % 2 == 0 else 0)): direction = ((direction[0] + 1) % 2, direction[1] * (1 if ((direction[0] + 1) % 2 == 1) else -1))
                        else: break
                    elif (layout[coords[1]][coords[0]] == "#"): 
                        coords[direction[0]] -= direction[1]
                        break
    final_x = current_face["x"] + coords[0]
    final_y = current_face["y"] + coords[1]
    print(f"Part 2: {1000 * final_y + 4 * final_x + (3 - sum(direction))}")

Part_2()
