inf = 10**9

def bf(n, list_ady, peso):
    pi = {i: inf for i in range(n + 1)}
    pi[0] = 0
    for i in range(n + 1):
        for u in list_ady:
            for v in list_ady[u]:
                p = peso[u,v] 
                if (pi[u] + peso[(u, v)]) < pi[v]:
                    pi[v] = pi[u] + peso[(u, v)]
    # corre una vez más para ver si hay ciclo negativo
    for u in list_ady:
        for v in list_ady[u]:
            if pi[u] != inf and (pi[u] + peso[(u, v)]) < pi[v]:
                return True
    return False


def main():
    res = []
    entrada = input().split()
    while entrada != ['0']:
        n = int(entrada[0])
        m = int(entrada[1])
        list_ady = {i: [] for i in range(n+ 1)}
        peso = {}
        i = 0
        while i < m:
            si, ni, oi, ki = map(str,input().split())
            si = int(si)
            ni = int(ni)
            ki = int(ki)
            if oi == "gt":
                if((si-1) in list_ady[si + ni]):
                        peso[(si + ni, si - 1)] =min(peso[(si + ni, si - 1)], -(ki + 1)) ##si no encontre una arista menor no la pongas
                else:
                    list_ady[si + ni].append(si-1)
                    peso[(si + ni, si - 1)] = -(ki + 1)
            else:
                if oi == "lt":
                    if (si + ni) in list_ady[si - 1]:
                        peso[(si - 1 ,si + ni)] =min(ki - 1, peso[(si - 1 ,si + ni)]) 
                    else:        
                        list_ady[si - 1].append(si + ni)
                        peso[(si - 1, si + ni)] = ki - 1
            i += 1

        hay_ciclo_neg = bf(n, list_ady, peso)
        if hay_ciclo_neg:
            res.append("successful conspiracy")
        else:
            res.append("lamentable kingdom")

        entrada = input().split()

    for result in res:
        print(result)

main()