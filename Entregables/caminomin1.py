import heapq

def pasarCasos():
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

def caminoMin():
    casos = pasarCasos()
    for caso in casos:
        n = caso[0]  # Número de ascensores
        k = caso[1]  # Piso objetivo
        tiempos = caso[2]  # Tiempos de cada ascensor
        ascensores = caso[3]  # Lista de pisos que visita cada ascensor
        
        grafico = construirGrafo(n, tiempos, ascensores)
        
        resultado = dijkstra(grafico, n, k)
        if resultado == float('inf'):
            print("IMPOSSIBLE")
        else:
            print(resultado)

def construirGrafo(n, tiempos, ascensores):
    grafico = [[] for _ in range(100)]  # Inicializar grafo de 0 a 99 pisos
    
    # Agregar conexiones entre pisos dentro de cada ascensor
    for i in range(n):
        pisos = ascensores[i]
        for j in range(len(pisos)):
            for l in range(j + 1, len(pisos)):
                u, v = pisos[j], pisos[l]
                cost = abs(v - u) * tiempos[i]
                grafico[u].append((v, cost))
                grafico[v].append((u, cost))
    
    # Agregar conexiones con costo de cambio de ascensor (60 segundos)
    for piso in range(100):
        for i in range(n):
            if piso in ascensores[i]:
                for j in range(n):
                    if i != j and piso in ascensores[j]:
                        grafico[piso].append((piso, 60))
    
    return grafico

def dijkstra(grafico, n, objetivo):
    dist = {v: float('inf') for v in range(100)}
    dist[0] = 0
    cola_prioridad = [(0, 0)] 
    
    while cola_prioridad:
        d, u = heapq.heappop(cola_prioridad)
        
        if u == objetivo:
            break
        
        if d > dist[u]:
            continue
        
        for v, peso in grafico[u]:
            if dist[v] > dist[u] + peso:
                dist[v] = dist[u] + peso
                heapq.heappush(cola_prioridad, (dist[v], v))
    
    return dist[objetivo]

# Llamada a la función principal para iniciar el procesamiento de casos
caminoMin()
