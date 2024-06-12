from re import findall, search

input = open("Day 21.txt").read()
lines = input.split("\n")
monkeys = {}

for l in lines:
    l = l.split(": ")
    variables = findall(r"[a-zA-Z]+", l[1])
    if (len(variables) > 0): monkeys[l[0]] = {"variables": variables, "equation": l[1]}
    else: monkeys[l[0]] = {"equation": int(l[1])}

def get(name):
    monkey = monkeys[name]
    if ("variables" in monkey): return eval(monkey["equation"], {v: get(v) for v in monkey["variables"]})
    else: return monkey["equation"]

def find(name, history):
    monkey = monkeys[name]
    history.append(name)
    if (name == "humn"): return True, history
    if ("variables" not in monkey): return False, history
    for v in monkey["variables"]:
        result, h = find(v, history.copy())
        if (result): return result, h
    else: return False, history

def Part_2():
    sides = findall(r"[a-zA-Z]+", monkeys["root"]["equation"])
    i = 1
    for s in sides:
        result, history = find(s, [])
        if (result): break
        else: i -= 1
    value = get(sides[i]) 
    for h in history[0: -1]:
        monkey = monkeys[h]
        sign = search(r"[+\-*\/]", monkey["equation"]).group()
        not_in = list(filter(lambda m: m not in history, monkey["variables"]))[0]
        v = monkey["variables"]
        match sign:
            case "+": value -= get(not_in)
            case "-": value = get(not_in) + value * (1 if (v.index(not_in) == 1) else -1)
            case "*": value /= get(not_in)
            case "/": value = eval(f"{get(not_in)} {'*' if (v.index(not_in) == 1) else '/'} {value}")
    print(f"Part 2: {int(value)}")

print(f"Part 1: {int(get("root"))}")
Part_2()