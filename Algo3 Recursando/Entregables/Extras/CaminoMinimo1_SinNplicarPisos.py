def distancia_minima(n , k , tiempos_ascensores, pisos_donde_para_iesimo):
    list_ady = {i: [] for i in range(100)}
    for i in range(n):
        pisos = pisos_donde_para_iesimo[i]
        for a in range(len(pisos)):
            for s in range(a + 1, len(pisos)): ##siemrpe para adelante
                actual = pisos[a]
                sigs = pisos[s]
                tiempo_ir = abs(sigs - actual) * tiempos_ascensores[i]
                list_ady[actual].append((sigs, tiempo_ir))
                list_ady[sigs].append((actual, tiempo_ir))
    pi = {i: float('inf') for i in range(100)}
    pi[0] = 0
    cola_prioridad = [(0, 0)] 
    visitados = set()
    
    while cola_prioridad:  # while S != Vacio
        cola_prioridad.sort()  #ordenalo
        piu, u = cola_prioridad.pop(0) #popea primer elemento
        if not(u in visitados): # si ya lo visite quiere decir que encontre cam minimo ahcia el, no enetres devuelta
            visitados.add(u)
            if u == k: #llegue al nodo que queria
                if pi[k] == float('inf'):
                    return "IMPOSSIBLE"
                else:
                    if k == 0:
                        return pi[k]
                    else:
                        return pi[k] - 60
            #si  no
            for v, tiempo_ir in list_ady[u]:
                if pi[v] > piu + tiempo_ir + 60:
                    pi[v] = piu + tiempo_ir + 60
                    cola_prioridad.append((pi[v], v))

def calcular_todos_los_datos():
    res = []
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
            i = 0
            while i < n:
                pisos_donde_paran_iesimo.append(list(map(int, input().split())))
                i += 1
            res.append(distancia_minima(n, k, tiempo_para_cada_ascensor, pisos_donde_paran_iesimo))

        except EOFError:
            break
    for r in res:
        print(r)

calcular_todos_los_datos()