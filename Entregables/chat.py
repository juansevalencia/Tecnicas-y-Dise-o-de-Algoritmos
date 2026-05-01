import heapq

def procesar_caso(caso):
    cant_edificios, piso, tiempo, ascensores = caso
    grafico = [[] for _ in range(100)]
    
    for i in range(cant_edificios):
        pisos = ascensores[i]
        for j in range(len(pisos)):
            for l in range(j + 1, len(pisos)):
                u, v = pisos[j], pisos[l]
                costo = abs(v - u) * tiempo[i]
                grafico[u].append((v, costo))
                grafico[v].append((u, costo))
    
    distancias = algoritmo_dijkstra(grafico, 0, piso)
    
    if distancias[piso] == float('inf'):
        return "IMPOSSIBLE"
    else:
        return distancias[piso] - 60 if piso != 0 else distancias[piso]

def relajar_arista(u, v, peso, distancias, cola_prioridad):
    if distancias[v] > distancias[u] + peso + 60:
        distancias[v] = distancias[u] + peso + 60
        heapq.heappush(cola_prioridad, (distancias[v], v))

def obtener_entradas():
    casos = []
    while True:
        try:
            entrada = input().strip()
            if not entrada:
                break
                
            cant_edificios, piso = map(int, entrada.split())
            tiempo = list(map(int, input().split()))
            ascensores = []
            for i in range(cant_edificios):
                ascensores.append(list(map(int, input().split())))
            casos.append([cant_edificios, piso, tiempo, ascensores])
        except EOFError:
            break
    return casos

def inicializar_fuente(grafico, s):
    distancias = {v: float('inf') for v in range(100)}
    distancias[s] = 0
    return distancias


def algoritmo_dijkstra(grafico, s, objetivo):
    distancias = inicializar_fuente(grafico, s)
    cola_prioridad = [(0, s)]
    
    while cola_prioridad:
        distancia_actual, u = heapq.heappop(cola_prioridad)
        if u == objetivo:
            break
        if distancia_actual > distancias[u]:
            continue
        for v, peso in grafico[u]:
            relajar_arista(u, v, peso, distancias, cola_prioridad)
    return distancias


def imprimir_tiempos_minimos():
    casos = obtener_entradas()
    for caso in casos:
        resultado = procesar_caso(caso)
        print(resultado)

imprimir_tiempos_minimos()
