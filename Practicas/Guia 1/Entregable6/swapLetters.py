def swapLetters(tam):
    global t
    global s
    swaps = 0
    i = 0
    result = []
    while(i < tam):
        if(s[i] == t[i]):
            i = i + 1
        else:
            cambioRap = indiceCambioRapido(i ,tam) 
            if(cambioRap < tam):
                save = s[i]
                s[i] = t[cambioRap]
                t[cambioRap] = save
                result.append([i + 1 , cambioRap + 1]) 
                i = i + 1
            else:
                cambioLen = indicePreCambioRapido(i ,tam)
                if(cambioLen < tam):
                    save = s[cambioLen]  
                    s[cambioLen] = t[cambioLen]
                    t[cambioLen] = save
                    result.append([cambioLen + 1 , cambioLen + 1])
                else:
                    return [-1]
    return result         

def indiceCambioRapido(i , tam ):
    global t 
    global s
    k = i + 1
    while(k < tam):
        if(t[k] != s[k] and s[i] != t[k]):
            return k
        else:
            k = k + 1
    return k            

def indicePreCambioRapido(i , tam):
    global t
    global s
    k = i + 1
    while(k < tam):
        if(t[k] != s[k]):
            return k
        else:
            k = k + 1
    return k       

def cantidadDif(p, q):
    rescuak = 0
    i = 0
    while(i < len(p)):
        if(p[i] != q[i]):
            rescuak += 1
        i +=1
    return rescuak

def main():
    tam = int(input())
    global t
    global s
    t = list(input())
    s = list(input())
    if(s == t):
        print("0")
    else:    
        if(cantidadDif(s,t) % 2 != 0)or len(t)!= tam or len(s) != tam or (tam == 1 and t[0] != s[0]):
            print(-1)
        else:    
            res = swapLetters(tam)
            if(res[0] == -1):
                print(res[0])
            else:
                print(len(res))    
                for r in res:
                    print(r[0] , r[1])

main()
