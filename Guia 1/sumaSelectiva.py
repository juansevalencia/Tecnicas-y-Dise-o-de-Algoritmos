'''
Supongamos que tenemos una Sopt y esta solucion optima es mejor que nuestra solucion greedy
Bueno entonces esto nos esta diciendo que la suma para el i esimo resultado de nuestra (Ri)
solucion optima va a tener que ser menor que la suma para el i esimo resultado de nuestra solución greedy (Gi)
Bueno entonces quiere decir que Gi >= Ri , bueno pero nosotros sabemos que eso no va  apasar por nuestra estrategia. Ya que por cada posición no puede pasar que Ri < a Gi ya que Gi esta 
arrancando con los minimos, de ultima puede ser igual pero no más. Los valores que arrastra Gi ,osea la primer parte de la suma , necesariamente van a ser menores o iguales que la primera parte de la sunma de Ri
porque sumaste los minimos. Y la segunda parte de la suma va a pasar lo mismo porque va a ser el i esimo numero, este si podria ser mas chico para Ri , pero si Ri es mas chico ahi va a ser
mas grande en la primera parte lo cual lo va hacer mas grande en general porque lo va a sumar en cada iteracion al mayor que puso antes.

'''

import heapq

def sumaselectivaB(lista , k):
    for i in range(k):
        max = lista[0]
        for j in range(1 , len(lista)):
            if(max < lista[j]):
                max = lista[j]
        lista.remove(max)         

def sumselectivahs(lista , k):
    res1 = heapsort(lista)
    res = []
    for i in range(0 , k):
        res.append(res1[i])

def heapsort(arr):
    heapq.heapify(arr)
    sorted_list = []
    while arr:
        sorted_list.append(heapq.heappop(arr))  # Extrae el elemento más pequeño del montículo
    return sorted_list

def sumagolosa(lista):
    res = heapsort(lista)
    ul = res[0]
    for k in range(1, len(res)):
        res1 = ul + res[k]
    
