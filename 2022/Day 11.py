from re import findall, search

input = open("Day 11.txt").read()
m = input.split("\n\n")
monkeys = []
primes = 1

def create_monkeys():
    global monkeys, primes
    for i in range(len(m)):
        info = m[i].split("\n")
        monkey = {"id": i, "inspected": 0}
        for line in info:
            if ("Starting items" in line): 
                monkey["items"] = [int(n) for n in findall(r"[0-9]+", line)]
                monkey["original"] = monkey["items"].copy()
            elif ("Operation" in line): monkey["operation"] = search(r"old [\+\-\*\/] [0-9(old)]+", line).group()
            elif ("Test" in line): monkey["test"] = int(search(r"[0-9]+", line).group())
            elif ("true" in line): monkey["True"] = int(search(r"[0-9]+", line).group())
            elif ("false" in line): monkey["False"] = int(search(r"[0-9]+", line).group())
        monkeys.append(monkey)
    for monkey in monkeys: primes *= monkey["test"] 

def inspection(rounds, division, modulus):
    for n in range(rounds):
        for monkey in monkeys:
            while (len(monkey["items"]) > 0):
                monkey["inspected"] += 1
                item = int(eval(monkey["operation"], {"old": monkey["items"].pop()}) / division) % modulus
                monkeys[monkey[str(item % monkey["test"] == 0)]]["items"].append(item)

    inspect = sorted([monkey["inspected"] for monkey in monkeys], reverse = True)
    return inspect[0] * inspect[1]

def Part_1():
    product = inspection(20, 3, float("inf"))
    print(f"Part 1: {product}")

def Part_2():
    product = inspection(10000, 1, primes)
    print(f"Part 2: {product}")

create_monkeys()
Part_1()
Part_2()