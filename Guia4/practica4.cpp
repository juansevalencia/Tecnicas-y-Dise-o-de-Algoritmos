import queue
def main():
    aristas = []
    dfs(lista_de_adyacencias , vertice , visitados,pesos)
    return aristas

def dfs(lista_de_adyacencias, vertice, visitados=None, aristas = None):
    if visitados is None:
        visitados = [False] * len(lista_de_adyacencias)
    visitados[vertice] = True
    # Hacer algo con el v´ertice
    for hijo in lista_de_adyacencias[vertice]:
        if not visitados[hijo]:
            aristas.append([vertice, hijo])
            dfs(lista_de_adyacencias, hijo, visitados, aristas)
        else:
            aristas.append([vertice, hijo])

## ejercicio 6
def bfs(lista_de_adyacencias, raiz, distancias, pesos_aristas):
    a_visitar = Queue()
    distancias = [-1] * len(lista_de_adyacencias)
    a_visitar.put(raiz)
    distancias[raiz] = 0
    while not a_visitar.empty():
        actual = a_visitar.get()
        for vecino in lista_de_adyacencias[actual]:
            minor = menorPeso(distancias, actual ,vecino, pesos_aristas, lista_de_adyacencias[vecino])
            if distancias[vecino] == -1:
                if(minor == actual):
                    distancias[vecino] = distancias[actual] + 1
                    a_visitar.put(vecino)
                else:
                    distancias[vecino] = distancias[actual] + 1
                    a_visitar.put(vecino)

    return distancias

def menorPeso(distancia , vertice, vecino, pesos_aristas, lista_de_adyacencias_v):
    min = lista_de_adyacencias_v[0]
    n = distancia[vertice]
    for mismoNivelArista in lista_de_adyacencias_v:
        if(distancia[mismoNivelArista] == n and pesos_aristas[min, vecino] > pesos_aristas[mismoNivelArista, vecino]){
            min = mismoNivelArista
        }
    return min

##ejercicio 7 
def minLongPar(lista_de_adyacencias, distancias , s , t, padre):
    a_visitar = Queue()
    distancias = [-1] * len(lista_de_adyacencias)
    a_visitar.put(s)
    distancias[s] = 0
    while not a_visitar.empty() and actual != t:
        actual = a_visitar.get()
        for vecino in lista_de_adyacencias[actual]:
            if distancias[vecino] == -1:
                distancias[vecino] = distancias[actual] + 1
                padre[vecino] = actual
                a_visitar.put(vecino)
    x = []
    recorredor = t
    list = []
    while x > 0 :
        list.append(recorredor)
        recorredor = padre[recorredor]
        x - 1
    if(len(list) % 2 == 0 ):
        return list
    else:
    ##busca un nodo entre medio que conecte con alguna arista
        for u in list:
            if(u != s):
                for z1 in lista_de_adyacencias[padre[u]]:
                    for z2 in lista_de_adyacencias[z1]: 
                        if(z2 == u):
                            cpy1 = list[:u]
                            cpy1.append(z1)
                            cpy2 = list[u:]
                            list = cpy1 + cpy2
                            res = 1
        if res == 1:
            return list
        else:
            delete(lista_de_adyacencias[padre[t]] , t)
            minLongPar(lista_de_adyacencias , distancias , s , t, padre )

##ejercicio 8

def caminoMinimoParaCero(k , w , x, y , grilla ):
    lista_adyacencia = {} ##crear 
    x1 = 0
    y1 = 0
    while(x1 < len(grilla)):
        while(y1 < len(grilla[0])):
            res = []
            for (dx, dy) in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                (x2, y2) = (x1 + dx, y1 + dy)
                if (1 <= x2 <= len(grilla) and 1 <= y2 <= len(grilla[1])):
                    res.append(grilla[x2, y2])
        lista_adyacencia[grilla[x1][y1]] = res 
    ##ya meti todos los valores en la lista de adyacencia
    C = Queue()
    raiz = grilla[x][y]
    value[raiz] = grilla[x][y]
    while(C != []):
        u = C.pop()
        for vecino in lista_adyacencia[u]:
            if(not(visitado[vecino])):
                padre[vecino] = u
                value[vecino] = (u + vecino) % k
    ##recorre todos los nodos, lleva un valor por cada recorrido            