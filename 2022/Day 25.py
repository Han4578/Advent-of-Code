input = open("Day 25.txt").read()
snafus = input.split("\n")
order = ["=", "-", "0", "1", "2"]

def decrypt(snafu):
    n = 0
    for i, s in enumerate(snafu[::-1]): n += (order.index(s) - 2) * 5 ** i
    return n

def encrypt(n):
    remaining = n
    digits = [0]
    while (remaining > 0):
        digits.append(remaining % 5)
        remaining = int(remaining / 5)
    for i, d in enumerate(digits):
        if (d > 2): digits[i + 1] += 1
        digits[i] = order[d - 3]
    if (digits[0] == "0"): digits.pop(0)
    return "".join(digits[::-1])

def Part_1():
    total = sum(decrypt(snafu) for snafu in snafus)
    print(f"Part 1: {encrypt(total)}")

Part_1()