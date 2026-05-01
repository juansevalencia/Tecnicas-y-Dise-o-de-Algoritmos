import heapq
from collections import defaultdict

def solve_security_cost(n, edges):
    # Grafo como lista de adyacencia
    graph = defaultdict(list)
    for v, w, c in edges:
        graph[v].append((w, c))
        graph[w].append((v, c))
    
    # Dijkstra para encontrar distancias mínimas
    def dijkstra(start, end):
        distances = [float('inf')] * n
        distances[start] = 0
        predecessors = [[] for _ in range(n)]
        pq = [(0, start)]
        
        while pq:
            current_dist, current_node = heapq.heappop(pq)
            
            if current_node == end:
                break
            
            if current_dist > distances[current_node]:
                continue
            
            for neighbor, edge_length in graph[current_node]:
                distance = current_dist + edge_length
                
                if distance < distances[neighbor]:
                    distances[neighbor] = distance
                    predecessors[neighbor] = [(current_node, edge_length)]
                    heapq.heappush(pq, (distance, neighbor))
                elif distance == distances[neighbor]:
                    predecessors[neighbor].append((current_node, edge_length))
        
        return distances[end], predecessors
    
    # Encontrar caminos mínimos
    min_distance, predecessors = dijkstra(0, n-1)
    
    # Marcar y calcular costo de calles en caminos mínimos
    security_cost = 0
    visited_edges = set()
    
    def trace_paths(node):
        nonlocal security_cost
        for prev_node, edge_length in predecessors[node]:
            # Asegurar que no contamos la misma calle dos veces
            edge = tuple(sorted((prev_node, node)))
            if edge not in visited_edges:
                visited_edges.add(edge)
                security_cost += 2 * edge_length
            
            trace_paths(prev_node)
    
    trace_paths(n-1)
    
    return security_cost

# Función de entrada
def main():
    n, m = map(int, input().split())
    edges = []
    
    for _ in range(m):
        v, w, c = map(int, input().split())
        edges.append((v, w, c))
    
    result = solve_security_cost(n, edges)
    print(result)

# Ejecutar solo si se corre directamente el script
if __name__ == "__main__":
    main()