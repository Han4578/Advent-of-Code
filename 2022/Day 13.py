input = open("Day 13.txt").read()
pairs = input.split("\n\n")
list_of_lists = [[eval(s) for s in pair.split("\n")] for pair in pairs]

def compare_lists(a, b):
    for i in range(len(a)):
        if (i == len(b)): return -1
        if (isinstance(a[i], list) or isinstance(b[i], list)):
            if (isinstance(a[i], int)): results = compare_lists([a[i]], b[i])
            elif (isinstance(b[i], int)): results = compare_lists(a[i], [b[i]])
            else: results = compare_lists(a[i], b[i])
            if (results != 0): return results
        else:
            if (a[i] < b[i]): return 1
            elif (a[i] > b[i]): return -1
    if (len(a) < len(b)): return 1
    else: return 0  

def Part_1():
    total = 0
    for index in range(len(list_of_lists)):
        pair = list_of_lists[index]
        if (compare_lists(pair[0], pair[1]) == 1): 
            total += index + 1      

    print(f"Part 1: {total}")

def Part_2():
    unpacked = [[[2]], [[6]]]
    for l in list_of_lists: unpacked += l
    total = reduce = 1
    has_sorted = True
    while (has_sorted):
        has_sorted = False
        for i in range(0, len(unpacked) - reduce):
            if (compare_lists(unpacked[i], unpacked[i + 1]) == -1): 
                unpacked[i], unpacked[i + 1] = unpacked[i + 1], unpacked[i]
                has_sorted = True
        reduce += 1
    for i in range(len(unpacked)): 
        if (str(unpacked[i]) in ["[[2]]", "[[6]]"]): total *= i + 1

    print(f"Part 2: {total}")

Part_1()
Part_2()



def create_list(string):
    converted = []
    i = 0
    new_num = False
    while (i < len(string)):
        match string[i]:
            case ",": new_num = True
            case "[": 
                converted.append(create_list(string[i + 1: len(string)]))
                i += len(str(converted[-1]).replace(" ", "")) - 1
            case "]": return [int(n) if isinstance(n, str) else n for n in converted]
            case _: 
                if (len(converted) == 0 or isinstance(converted[-1], list) or new_num): converted.append("")
                converted[-1] += string[i]
                new_num = False
        i += 1
    return [int(n) if isinstance(n, str) else n for n in converted]