def main():
    tam = int(input())
    s = list(input())
    t = list(input())
    if(s == t):
        print("0")
    else:    
        i = 0
        dif_a = []
        dif_b = []
        while(i < tam):
            if(s[i] != t[i]):
                if(s[i] == "b"):
                    dif_a.append(i)
                else:
                    dif_b.append(i)
            i = i + 1
        res1 = 0 
        res = []
        k = 0
        if((len(dif_a) + len(dif_b)) % 2 == 0 ): ## and (len(dif_a) == len(dif_b))
                i = 0
                while(i + 1 < len(dif_a)):
                    res.append([dif_a[i] + 1 ,dif_a[i + 1] + 1])
                    res1 += 1
                    i += 2
                j = 0
                while(j + 1 < len(dif_a)):
                    res.append([dif_b[j] + 1 ,dif_b[j + 1] + 1])
                    res1 += 1
                    j += 2
                if(j < len(dif_a)):
                    res.append([dif_a[i] + 1 , dif_a[i] + 1])
                    res.append([dif_a[i] + 1 , dif_b[i] + 1])
                    res1 += 2
        else:
            k = 1
            print(-1)    
        if(k == 0):
            print(res1)
            for i in res:
                print(i[0] , i[1])


main()