def pasarCasos():
    casos = []
    while True:
        try:
            entrada = input().strip()
            if not entrada:
                break
                            
            cant_edificios, piso = map(int, entrada.split())
            tiempo = list(map(int, input().split()))
            asc = []
            for i in range(cant_edificios):
                asc.append(list(map(int, input().split())))
            casos.append([cant_edificios, piso, tiempo, asc])
        except EOFError:
            break
    return casos

def caminoMin():
    res = []
    casos = pasarCasos()
    for caso in casos:
        grafo = [[] for _ in range(100)]
        k = caso[1]
        n = caso[0]
        vertices = {}
        tiempos = caso[2]
        i = 1
        while(i <= n):
            pisos = caso[3][i-1]
            ant = 0
            r = 1
            for pison in pisos:
                vertices[(pison, i)] = 1 ##presente
                if(r == 1):
                    ant = pison
                    list_ady[(ant,i)] = []
                    r = r - 1
                else:
                    aristas[((ant, i),(pison,i))] = (pison - ant)*tiempos[i-1]
                    aristas[(pison, i),(ant, i)] = (pison - ant)*tiempos[i-1]
                    list_ady[(pison, i)] = [(ant, i)]
                    list_ady[(ant,i)].append((pison, i))
                    ant = pison
            list_ady[(pison, i)] = []        
            i +=1
                #agreguemos aristas de costo 60 entre
        arrancan_cero = []
        for j in range(1, n + 1):
            if (0,j) in vertices:
                arrancan_cero.append(j)
        for ascensor1 in arrancan_cero:
            for ascensor2 in arrancan_cero:
                if(ascensor1 != ascensor2):
                    aristas[((0, ascensor1), (0, ascensor2))] = 0 ##ya puse todos los inicos con costo 0 entre si asi puedo iniciar djikstra en cualquiera
                    list_ady[(0,ascensor1)].append((0, ascensor2))
        for piso in range(1,99): ##si quiero bajar tiempo pongo aca una lista de pisos que la completo antes (no lo hice)
            for ascensor1 in range(1, n + 1):
                if((piso,ascensor1) in vertices):
                    for ascensor2 in range(1, n+1):
                        if(ascensor1 != ascensor2): 
                            if (piso,ascensor2) in vertices :
                                aristas[(piso,ascensor1), (piso,ascensor2)] = 60
                                if((piso, ascensor1) in list_ady):
                                    list_ady[(piso, ascensor1)].append((piso, ascensor2))
                                else:
                                    list_ady[(piso, ascensor1)]= [(piso, ascensor2)]
                #camino min dijkstra 
        if len(arrancan_cero) == 0:
            res.append("IMPOSSIBLE")
        else:
            respuesta = djikstra(aristas, arrancan_cero[0], list_ady,vertices,k) 
            if(respuesta == 100001):
                res.append("IMPOSSIBLE")
            else:    
                res.append(respuesta)
    for sol in res:
        print(sol)

def djikstra(aristas , ascensor_estoy_arriba, vecinos, vertices, k):
    difVyS = {} #estan en V y no en S
    for nodo in vertices:
        difVyS[nodo] = 1
    del difVyS[(0,ascensor_estoy_arriba)]
    pi = {}
    pi[(0,ascensor_estoy_arriba)] = 0
    for vertice in vertices:
        pi[vertice] = 10001
    for vertice in vecinos[(0, ascensor_estoy_arriba)]:
        pi[vertice] = aristas[(0, ascensor_estoy_arriba),(vertice)]
    S = {}
    S[(0,ascensor_estoy_arriba)] = 1
    while S != vertices:
        w = menorDist(pi, difVyS) ##quiero el vertice de menor distancia a v (v es el piso 0) que no este en S
        del difVyS[w]
        S[w] = 1
        for vec in difVyS :
            if vec in vecinos[w]:
                if(pi[w] + aristas[(w,vec)] < pi[vec]):
                    pi[vec] = pi[w] + aristas[(w,vec)]
    
    minN = (k, 100001) ##piso | costo
    for distancia in pi: ##busco entre todas las distancias las q tengan el piso en k y la que sea menor
        if distancia[0] == k and pi[distancia] < minN[1]:
           minN = (distancia[0], pi[distancia])
    return minN[1]       

            
def menorDist(pi, difVyS):
    min = (0,10002)
    for i in difVyS:
        if(pi[i] < min[1]): 
            min = (i,pi[i])
    return min[0]

caminoMin()