def bellman_ford(n, m, subsecuencias):
    # Inicializamos el grafo
    graph = {i: [] for i in range(n + 1)}
    
    # Procesamos cada subsecuencia
    for si, ni, oi, ki in subsecuencias:
        if oi == 'gt':
            for start in range(si, si + ni):
                for end in range(start + 1, si + ni + 1):
                    graph[start].append((end, ki))
        elif oi == 'lt':
            for start in range(si, si + ni):
                for end in range(start + 1, si + ni + 1):
                    graph[start].append((end, -ki))
    
    # Bellman-Ford desde el nodo 0
    dist = {i: float('inf') for i in range(n + 1)}
    dist[0] = 0
    
    for _ in range(n):
        for u in range(n + 1):
            if dist[u] == float('inf'):
                continue
            for v, weight in graph[u]:
                if dist[u] + weight < dist[v]:
                    dist[v] = dist[u] + weight
    
    # Revisamos si hay ciclo negativo
    for u in range(n + 1):
        if dist[u] == float('inf'):
            continue
        for v, weight in graph[u]:
            if dist[u] + weight < dist[v]:
                return "successful conspiracy"
    
    return "lamentable kingdom"

def solve():
    import sys
    input = sys.stdin.read().strip().split("\n")
    
    idx = 0
    results = []
    
    while idx < len(input):
        line = input[idx].strip()
        if line == '0':
            break
        
        n, m = map(int, line.split())
        subsecuencias = []
        
        for _ in range(m):
            idx += 1
            si, ni, oi, ki = input[idx].split()
            si = int(si)
            ni = int(ni)
            ki = int(ki)
            subsecuencias.append((si, ni, oi, ki))
        
        result = bellman_ford(n, m, subsecuencias)
        results.append(result)
        
        idx += 1
    
    for result in results:
        print(result)

solve()