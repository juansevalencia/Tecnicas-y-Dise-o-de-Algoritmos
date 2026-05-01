def CETDBU(j, cortes):
    cortesaux = [0] + cortes + [j] 
    for k in cortes : #mi logica es  itero dentro de todos los cortes , y por cada uno busco cual es que suma longitud minima teniendo en cuenta que la longitud seria la resta de minAdelante y MinAtras donde min adelante y minAtras seria el menor corte o pared que puedo tener adelante y atras respectivamente
        for c in cortes:
            minAnt = ant(cortesaux, c)
            minAd = sig(cortesaux, c)def CETDBU(j , cortes):
    matriz =[[0] * (j + 1)  for _ in range(j + 1)]
    cortesaux = [0] + cortes + [j] 
    res = 0
    for c in cortes:
            minAnt = ant(cortesaux , c)
            minAd = sig(cortesaux , c)
            long = minAd - minAnt 
            res += long
            cortesaux.remove(c)
    return res
            long = minAd - minAnt 
            res += long
            cortesaux.remove(c)
        return res

def ant(cortesaux, c):
    for i in range(len(cortesaux)):
        if cortesaux[i] == c:
            return cortesaux[i-1]

def sig(cortesaux, c):
    for i in range(len(cortesaux)):
        if cortesaux[i] == c:
            return cortesaux[i+1]

# Ejemplo de uso
cortes = [2, 4, 7]
j = 10
resultado = CETDBU(j, cortes)
print(resultado)
