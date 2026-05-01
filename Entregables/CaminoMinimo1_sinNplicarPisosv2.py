import sys
from collections import defaultdict

class Graph():
    ##implementacion grafo basada en geeks for geeks
    def __init__(self, vertices):
        self.V = vertices
        self.list_ady = defaultdict(list)

    def add_edge(self, u, v, weight):
        self.list_ady[u].append((v, weight))
        self.list_ady[v].append((u, weight))  

    def printSolution(self, dist):
        print("Vertex \tDistance from Source")
        for node in range(self.V):
            print(node, "\t", dist[node])
##djikstra geeks for geeks
    def dijkstra(self, src):
        dist = [sys.maxsize] * self.V
        dist[src] = 0
        pq = [(0, src)] 
        while pq:
            pq.sort()  
            piu, u = pq.pop(0)  
            if piu > dist[u]:
                continue
            for v, tiempo_ir in self.list_ady[u]:
                if dist[v] > dist[u] + tiempo_ir + 60:
                    dist[v] = dist[u] + tiempo_ir + 60
                    pq.append((dist[v], v))

        return dist


def almacenar_todos_los_datos():
    data_por_caso = []
    while True:
        try:
            entrada = input().strip()
            if not entrada:
                break
            entradastr = entrada.split()
            n = int(entradastr[0])
            k = int(entradastr[1])
            tiempo_para_cada_ascensor = list(map(int, input().split()))
            pisos_donde_paran_iesimo = []
            for i in range(n):
                pisos_donde_paran_iesimo.append(list(map(int, input().split())))
            data_por_caso.append((n, k, tiempo_para_cada_ascensor, pisos_donde_paran_iesimo))
        except EOFError:
            break
    return data_por_caso

def distancia_minima(info):
    n, k, tiempos_ascensores, pisos_donde_para_iesimo = info
    g = Graph(100) ##solucion a list_ady
    for i in range(n): 
        pisos = pisos_donde_para_iesimo[i]
        for a in range(len(pisos)):
            for s in range(a + 1, len(pisos)):  # siempre para adelante
                actual = pisos[a]
                sigs = pisos[s]
                tiempo_ir = abs(sigs - actual) * tiempos_ascensores[i]
                g.add_edge(actual, sigs, tiempo_ir)

    distancias = g.dijkstra(0) ##mismo check
    if distancias[k] == sys.maxsize:
        return "IMPOSSIBLE"
    else:
        if k == 0:
            return distancias[k]
        else:
            return distancias[k] - 60

def main():
    data_total = almacenar_todos_los_datos()
    for info in data_total:
        res = distancia_minima(info)
        print(res)

main()
