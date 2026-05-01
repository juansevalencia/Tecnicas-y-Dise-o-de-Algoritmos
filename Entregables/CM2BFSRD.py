import sys

def hayCicloNeg_BF(n, graph):
    inf = sys.maxsize
    dist = [inf] * (n + 1)
    dist[0] = 0

    for i in range(n):
        for u in range(len(graph)):
            for v, weight in graph[u]:
                if dist[u] + weight < dist[v]:
                    dist[v] = dist[u] + weight
    for u in range(len(graph)):
        for v, weight in graph[u]:
            if dist[u] != inf and dist[u] + weight < dist[v]:
                return True

    return False

def main():
    results = []

    while True:
        entrada = sys.stdin.readline().strip() 
        if entrada == "0":
            break
        input_lines = entrada.split()
        n = int(input_lines[0])
        m = int(input_lines[1])
        graph = [[] for _ in range(n + 1)]
        for _ in range(m):
            line = sys.stdin.readline().strip()
            s_i, n_i, o_i, k_i = line.split()
            s_i = int(s_i)
            n_i = int(n_i)
            k_i = int(k_i)
            if o_i == "lt":
                graph[s_i - 1].append((s_i + n_i, k_i - 1))
            elif o_i == "gt":
                graph[s_i + n_i].append((s_i - 1, -(k_i + 1)))
##Estaba teniendo el problema de que se me pisen los valores con lq list de adyacencia
        if hayCicloNeg_BF(n, graph):
            results.append("successful conspiracy")
        else:
            results.append("lamentable kingdom")

    for result in results:
        print(result)

main()
