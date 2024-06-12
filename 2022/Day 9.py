input = open("Day 9.txt").read()
motions = input.split("\n")

def move(tail_length):
    total = {}
    head = [0.0, 0.0]
    tails = [[0.0, 0.0] for n in range(tail_length)]
    for pair in motions:
        pair = pair.split(" ")
        for i in range(int(pair[1])):
            match pair[0]:
                case "U":
                    head[1] -= 1
                case "D":
                    head[1] += 1
                case "L":
                    head[0] -= 1
                case "R":
                    head[0] += 1
            for n in range(len(tails)):
                tail = tails[n]
                h = tails[n -1] if (n > 0) else head
                horizontal = h[0] - tail[0]
                vertical = h[1] - tail[1]
                if (not (abs(horizontal) == 2 or abs(vertical) == 2)): break
                if (abs(horizontal) == 2): tail[0] -= horizontal / abs(horizontal)
                if (abs(vertical) == 2): tail[1] -= vertical / abs(vertical)
                tail[0] += horizontal
                tail[1] += vertical
            total[str(tails[-1])] = 1
    return len(total.keys())

def Part_1():
    total = move(1)
    print(f"Part 1: {total}")

def Part_2():
    total = move(9)
    print(f"Part 2: {total}")

Part_1()
Part_2()