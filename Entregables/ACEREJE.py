import sys
def bellman_ford_detect_negative_cycle(n, graph):
    # Paso 1: Inicializar distancias
    dist = {i: sys.maxsize for i in range(n + 1)}
    dist[0] = 0


    # Paso 2: Relajar las aristas repetidamente
    for i in range(n):
        for u in sorted(graph):
            for v, weight in graph[u]:
                if dist[u] != sys.maxsize and dist[u] + weight < dist[v]:
                    dist[v] = dist[u] + weight
    

    # Paso 3: Verificar la existencia de ciclos negativos
    for u in graph:
        for v, weight in graph[u]:
            if dist[u] + weight < dist[v]:
                return True  # Se encontró un ciclo negativo

    return False  # No se encontraron ciclos negativos

def main():
    results = []
    while True:
        input_lines = list(map(str, input().split()))
        if len(input_lines) == 1 and input_lines[0] == '0':
            break
        else:
            n, m = map(int, input_lines)
        
        graph = {i: [] for i in range(n + 1)}  # Incluimos n + 1 para el vértice adicional s0=0
        
        for _ in range(m):
            s_i, n_i, o_i, k_i = input().split()
            s_i, n_i, k_i = int(s_i), int(n_i), int(k_i)
            end_vertex = s_i + n_i  # nodo destino
            if o_i == 'lt':
                weight = k_i - 1
                graph[s_i -1].append((end_vertex, weight))
            elif o_i == 'gt':
                weight = -(k_i + 1)
                graph[end_vertex].append((s_i -1, weight))

        if bellman_ford_detect_negative_cycle(n, graph):
            results.append("successful conspiracy")
        else:
            results.append("lamentable kingdom")

    print("\n".join(results))

main()