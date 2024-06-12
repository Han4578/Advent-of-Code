input = open("Day 2.txt", "r").read()
rounds = input.split("\n")

def Part_1():
    total = 0

    for r in rounds:
        r = r.split(" ")
        opponent = ord(r[0]) - 64
        me = ord(r[1]) - 87
        total += me

        if (me == opponent): total += 3
        elif (me - 1 == opponent % 3): total += 6
                
    print(f"Part 1: {total}")

def Part_2():
    total = 0

    for r in rounds:
        r = r.split(" ")
        opponent = ord(r[0]) - 64
        condition = ord(r[1]) - 87

        match condition:
            case 1: #lose
                total += (opponent - 2) % 3 + 1
            case 2: #draw
                total += opponent + 3
            case 3: #win
                total += opponent % 3 + 1 + 6
                
    print(f"Part 2: {total}")

Part_2()
Part_2()