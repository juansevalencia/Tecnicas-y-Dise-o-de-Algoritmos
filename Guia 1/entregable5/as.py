import sys

def main():
    tam = int(sys.stdin.readline().rstrip())
    s = sys.stdin.readline().rstrip()
    t = sys.stdin.readline().rstrip()

    dif_a = [i for i, (x, y) in enumerate(zip(s, t)) if x != y and x == 'b']
    dif_b = [i for i, (x, y) in enumerate(zip(s, t)) if x != y and x == 'a']

    res1 = 0
    res = []
    k = 0
    if (len(dif_a) + len(dif_b)) % 2 == 0:
        i = 0
        while i + 1 < len(dif_a):
            res.append([dif_a[i] + 1, dif_a[i + 1] + 1])
            res1 += 1
            i += 2
        j = 0
        while j + 1 < len(dif_b):
            res.append([dif_b[j] + 1, dif_b[j + 1] + 1])
            res1 += 1
            j += 2
        if j < len(dif_a):
            res.append([dif_a[i] + 1, dif_a[i] + 1])
            res.append([dif_a[i] + 1, dif_b[i] + 1])
            res1 += 2
    else:
        k = 1
        print(-1)
    if k == 0:
        print(res1)
        for i in res:
            print(i[0], i[1])

if __name__ == "__main__":
    main()
