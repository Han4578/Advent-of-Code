jet = open("Day 17.txt").read()
rocks = [[(0, 0), (1, 0), (2, 0), (3, 0)], [(0, 1), (1, 0), (1, 1), (1, 2), (2, 1)], [(0, 0), (1, 0), (2, 0), (2, 1), (2, 2)], [(0, 0), (0, 1), (0, 2), (0, 3)], [(0, 0), (1, 0), (0, 1), (1, 1)]]
obstacles = {}
start_loop = end_loop = loop_height = ori_height = jet_index = highest_point = 0
history_list = []
height_list = []

def get_obstacles(y):
    global obstacles
    if (y not in obstacles): obstacles[y] = []
    return obstacles[y]

def find_loop():
    global highest_point, jet_index, history_list, height_list, start_loop, end_loop, loop_height, ori_height
    for i in range(10000):
        rock = [[x  + 3, y + highest_point + 4] for x, y in rocks[i % len(rocks)]]
        while True:
            dir = 1 if (jet[jet_index % len(jet)] == ">") else -1
            if (all([(x + dir > 0 and x + dir < 8 and x + dir not in get_obstacles(y)) for x, y in rock])):
                for r in rock: r[0] += dir
            jet_index += 1
            if (all([x not in get_obstacles(y - 1) and y - 1 > 0 for x, y in rock])):
                for r in rock: r[1] -= 1
            else:
                for x, y in rock: get_obstacles(y).append(x)
                for y in sorted(obstacles.keys(), reverse = True):
                    if (len(get_obstacles(y)) > 0):
                        highest_point = y
                        break
                break
        current = (i % len(rocks), (jet_index - 1) % len(jet), ",".join([str(s) for s in obstacles[highest_point]]))
        history_list.append(current)
        height_list.append(highest_point)
        if (history_list.count(current) > 1):
            reversed_h = list([i for i, c in enumerate(history_list) if c == current].__reversed__())
            for ii, ri in enumerate(reversed_h[0:-1]):
                for iii, rii in enumerate(reversed_h[ii + 1:]):
                    if (all([history_list[ri - y] == history_list[rii - y]] for y in range(ri - rii))):
                        start_loop, end_loop, loop_height, ori_height = rii, ri, height_list[ri] - height_list[rii], height_list[rii]
                        return
    return highest_point

def find_height(n):
    if (n - 1 > end_loop): return ori_height + loop_height * int((n - (start_loop + 1)) / (end_loop - start_loop)) + height_list[start_loop + (n - (start_loop + 1)) % (end_loop - start_loop)] - ori_height
    else: return height_list[n - 1]

find_loop()
print(f"Part 1: {find_height(2022)}")
print(f"Part 2: {find_height(1000000000000)}")

    # if (n - 1 > end_loop):
    #     highest_point = ori_height
    #     n_loops = int((n - (start_loop + 1)) / (end_loop - start_loop))
    #     highest_point += loop_height * n_loops
    #     remaining = (n - (start_loop + 1)) % (end_loop - start_loop)
    #     highest_point += height_list[start_loop + remaining] - ori_height
    # else: highest_point = height_list[n - 1]
    # return highest_point