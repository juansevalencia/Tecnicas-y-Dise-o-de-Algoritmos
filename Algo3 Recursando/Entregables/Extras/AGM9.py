def contraseña():
    casos = int(input())
    p = 0
    result = []
    for p in range(0,casos):
        linea = input().split()
        cant_contraseñas = int(linea[0])
        contraseñas = []
        contraseñas_divididas_x_digito = []
        i = 0
        for i in range(1, len(linea)):
            contraseñas.append(int(linea[i])) #aca las pongo sin separar x digito
            contraseñai = []
            for digito in linea[i]:
                contraseñai.append(int(digito)) #separada x digito
            contraseñas_divididas_x_digito.append(contraseñai)
    ##queremos saber la distancia minima desde el punto de inicio hacia tdoas las contraseñas y asi sucesivamente.
        inicio = 0
        vertices = [inicio]
        aristas = {}
        for c in contraseñas:
            aristas[c] = []
        aristas_inicio = []
        costos = {}
        inicio_dividido_x_digito = [0, 0, 0, 0]
        i = 0
        for i in range(0, cant_contraseñas):
            vertices.append(contraseñas[i])
            aristas_inicio.append(contraseñas[i])
            c = minima_distancia( inicio_dividido_x_digito, contraseñas_divididas_x_digito[i])
            costos[(contraseñas[i],inicio)] = c
            costos[(inicio, contraseñas[i])] = c
        aristas[inicio] = aristas_inicio     
        i = 0
        j = 0
        for i in range(0, cant_contraseñas):
            for j in range(0, cant_contraseñas): ##para cada par de contraseñas distintos queremos calcular el costo también.
                if(i != j):
                    if((contraseñas[i],contraseñas[j]) in costos):
                        None
                    else:    
                        aristas[contraseñas[i]] = aristas[contraseñas[i]] + [contraseñas[j]]
                        aristas[contraseñas[j]] = aristas[contraseñas[j]] + [contraseñas[i]]
                        c = minima_distancia(contraseñas_divididas_x_digito[i], contraseñas_divididas_x_digito[j])
                        costos[(contraseñas[i],contraseñas[j])] = c
                        costos[(contraseñas[j],contraseñas[i])] = c
        ##Aplicar primm sobre el inicio
        i = 0
        resultchico = 0
        vertices_T = [inicio]
        while(i < cant_contraseñas): ## quiero buscar la mas chica que este conectada mi inicio, una vez que la a todas las que se relacionen con ella la pongo en peso 0 para las demas.
            min = 9999
            for posibles in vertices_T:
                for destinos_no_pertenecientes in aristas[posibles]:
                    if(destinos_no_pertenecientes in vertices_T):
                        None
                    else:
                        new = costos[(posibles, destinos_no_pertenecientes)]
                        if(new < min):
                            min = new
                            minV = destinos_no_pertenecientes
            resultchico += min
            vertices_T.append(minV)
            if i == 0:
                vertices_T.remove(inicio)
            i += 1
        result.append(resultchico)
    for res99 in result:
        print(res99)
                    

def minima_distancia(inicio, meta):
    cpy = inicio
    res = 0
    for i in range(0, 4):
        dst1 = abs(meta[i] - cpy[i])
        if(dst1 > 5):
            dst1 = abs(dst1 - 10)
        res += dst1
    return res

contraseña()