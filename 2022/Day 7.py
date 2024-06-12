from re import search

lines = open("Day 7.txt").read().split("\n")
main = {"size": 0, "id": 0}
sizes = []
current_dir = main[".."] = main["/"] = main
max_size = 100000

def get_size(dir):
    global sizes
    for key in dir.keys():
        if (key not in ["..", "size", "/", "id"]): dir["size"] += get_size(dir[key])
    sizes.append(dir["size"])
    return dir["size"]

def build_system():
    global current_dir
    i = 0
    for command in lines:
        i += 1
        if (command[0] != "$"): continue
        if (search("cd", command)): current_dir = current_dir[command.replace("$ cd ", "")]
        elif (search("ls", command)):
            ii = i
            if (ii >= len(lines)): continue
            line = lines[ii]
            while (line[0] != "$"):
                parts = line.split(" ")
                if (parts[0] == "dir"): current_dir[parts[1]] = {"..": current_dir, "size": 0}
                else: current_dir["size"] += int(parts[0])
                ii += 1
                if (ii < len(lines)): break
                line = lines[ii]
    get_size(main)

def Part_1():
    smol = filter(lambda n: n <= max_size, sizes)
    print(f"Part 1: {sum(smol)}")

def Part_2():
    max_size = main["size"] - 40000000
    beeg = filter(lambda n: n >= max_size, sizes)
    print(f"Part 2: {sorted(beeg)[0]}")

build_system()
Part_1()
Part_2()