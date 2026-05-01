import heapq

def getmeinput():
    casos_totales = []
    while True:
        try:
            entrada = input().strip()
            if not entrada:
                break
            n, k = map(int, entrada.split()) #n son la #asc y k el piso al q quiero llegar
            tiemposEnMoverse = list(map(int, input().split()))
            pisos = []
            for ascensores in range(n):
                pisos.append(list(map(int, input().split())))
            casos_totales.append([n, k , tiemposEnMoverse, pisos])
        #no tengo mas
        except EOFError:
            break
    return casos_totales

def devolver_res():
    casos_totales = getmeinput()
    for caso in casos_totales:
        res = grafo_dijkstra(caso)
        print(res)

def grafo_dijkstra(info_caso): 
    n = info_caso[0] 
    k = info_caso[1]
    tiempos_en_moverse = info_caso[2]
    pisos = info_caso[3]
    grafo = [[] for _ in range(100)] 
    for i in range(n):
        pisos_de_ascensor = pisos[i]
        for j in range(len(pisos_de_ascensor)):
            for sigs in range(j + 1 , len(pisos_de_ascensor)):
                vertice2 = pisos_de_ascensor[sigs]
                vertice1 = pisos_de_ascensor[j]
                time = abs(vertice2 - vertice1) * tiempos_en_moverse[i]
                grafo[vertice1].append((vertice2, time))
                grafo[vertice2].append(( vertice1, time))
    res = djikstra(grafo, k)

    if res != float('inf'):
        return res - 60 if k != 0 else res
    else:
        return "IMPOSSIBLE"

def djikstra(grafo, k):   
    pi = {v: float('inf') for v in range(100)}
    pi[0] = 0
    S = [(0, 0)]

    while S: #mientras no sea vacia
        data = heapq.heappop(S)
        piAcomparar = data[0]
        vertice1 = data[1]
        
        if vertice1 == k:
            break
        
        if piAcomparar > pi[vertice1]:
            continue

        for vertice2, time in grafo[vertice1]:
            if pi[vertice2] > pi[vertice1] + time + 60:
                pi[vertice2] = pi[vertice1] + time + 60
                heapq.heappush(S, (pi[vertice2], vertice2))
        
        return pi[k]

# llamamos a devolver res
devolver_res()


    
    
