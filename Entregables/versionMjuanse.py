import heapq

def pasarCasos():
    casos = []
    while True:
        try:
            entrada = input().strip()
            if not entrada:
                break
                            
            cant_edificios, piso = map(int, entrada.split())
            time = list(map(int, input().split()))
            elev = []
            for i in range(cant_edificios):
                elev.append(list(map(int, input().split())))
            casos.append([cant_edificios, piso, time, elev])
        except EOFError:
            break
    return casos

# Función para inicializar las distancias y padres
# Inicializo el vector distancias todos en INF, menos el nodo fuente s, que es por quien arranco (raiz)
def inicializar_fuente_unica(grafico, s):
    dist = {v: float('inf') for v in range(100)}
    dist[s] = 0
    return dist

# Función RELAJAR EXTRAIDA DEL CORMEN
# Lo que hace esta funcion, es: en caso de haber encontrado un camino mejor, actualiza las distancias nuevas encontradas, reemplazando la anterior
def relajar(u, v, peso, dist, cola_prioridad):
    
    #Si la distancia al nodo v es mayor que la distancia al nodo u + el peso de la arista entre u y v más 60 segundos,
    # se actualiza la distancia al nodo v, agregando al heap el nodo v con la nueva dist.
    if dist[v] > dist[u] + peso + 60:
        dist[v] = dist[u] + peso + 60
        heapq.heappush(cola_prioridad, (dist[v], v))


# Algoritmo de Dijkstra BASADA EN EL CORMEN (utiliza una cola de prioridad para manejar la extraccion del nodo con la minim dist y RELAJANDO SUS ARISTAS PARA actualizar distanciass)
#Realizo la busqueda del camino minimo de un nodo fuente (s), a todos los nodos adyacentes a este
def dijkstra(grafico, s, objetivo):
    dist = inicializar_fuente_unica(grafico, s)
    cola_prioridad = [(0, s)]
    
    while cola_prioridad:
        d, u = heapq.heappop(cola_prioridad)
        
        if u == objetivo:
            break
        
        if d > dist[u]:
            continue
        
        for v, peso in grafico[u]:
            relajar(u, v, peso, dist, cola_prioridad)
    
    return dist

# Función para procesar cada caso
def procesarCaso(caso):
    cant_edificios, piso, tiempo, ascensores = caso
    # Armo el grafico con los datos de las entradas, primero inicializándolo vacío
    grafico = [[] for _ in range(100)]
    
    for i in range(cant_edificios):
        pisos = ascensores[i] # caso[i][3]
        for j in range(len(pisos)): # itera sobre todos los pisos que puede recorrer el ascensor i
            for l in range(j + 1, len(pisos)): # itera sobre los pisos que viene después del piso actual pisos[j]
                u, v = pisos[j], pisos[l]
                cost = abs(v - u) * tiempo[i] # calculo la cantidad de pisos recorridos por el tiempo del edificio que estoy parada
                grafico[u].append((v, cost)) # almaceno en el grafico el costo de la arista entre el piso u y v
                grafico[v].append((u, cost)) # como se puede viajar en ambas direcciones, el costo será el mismo
    
    # Ahora utilizamos el algoritmo de Dijkstra para resolver el tiempo mínimo, utilizando una cola de prioridad en donde vamos encolando los pisos adyacentes
    dist = dijkstra(grafico,0,piso) # en dist se almacenan las distancias mínimas desde 0 a todos los demás pisos, cuya inicialización está en infinito pues al comienzo no calcule nada

    
    if dist[piso] == float('inf'):
        return "IMPOSSIBLE"
    else:
        return dist[piso] - 60 if piso != 0 else dist[piso]

# Función para imprimir los tiempos mínimos
def imprimir_tiempos_minimos():
    casos = pasarCasos()
    for caso in casos:
        resultado = procesarCaso(caso)
        print(resultado)

imprimir_tiempos_minimos()