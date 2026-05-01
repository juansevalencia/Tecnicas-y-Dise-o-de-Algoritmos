def main():
    resf = []
    cantEdificios = 6
    altura = [10, 100, 50, 30 ,80, 10]
    ancho = [50, 10 ,10 ,15 ,20 ,10]
    maior = mayorEmpinado(cantEdificios - 1, altura ,ancho,  {})
    menior = menorEmpinado(cantEdificios - 1 , altura ,ancho, {})
    nueva = (maior , menior)
    resf.append(nueva) #chequear que pasa si son iguales :0

    for k in range(0 , len(resf)):
        print(k, resf)
        if(resf[k][0] >= resf[k][1] ):
            return ("Case ", k ,". Increasing (" ,resf[k][0], "). Decreasing (" ,resf[k][1], ")." )
        else:
            return ("Case ", k ,". Decreasing (" ,resf[k][1], "). Increasing (" ,resf[k][0], ")." )

    
def mayorEmpinado(i , altura ,ancho, Amc , ms ):
##el dic Amc toma como clave el la i esima posicion y toma como clave una tupla con primer valor la suma del mayor empinado a partir de ahi y el segundo toma si tiene diferentes valores.
    elemAltura = [altura[i]]
    j = i + 1
    res1 = ancho[i]
    res2 =  ancho[i]
    yaCalculado = False
    while(j < len(altura) and altura[j] > altura[i]):
        resi = ancho[i]
        if(Amc.get(j) != None and (Amc.get(j) == True or altura[j] != altura[i])):
            resi = resi + Amc.get(j)
            elementos = Amc.get(j)
            yaCalculado = True
            if(ms < resi):
                ms = resi
            j = j + 1
        else:
            elemAltura = elemAltura.append(altura[j]) 
            res2 = res2 + ancho[j]
            j = j + 1
            
    if(yaCalculado):
        Amc[i] = res1 
        if(i == 0):
            return res1
        else:
            return max(res1 , mayorEmpinado(i - 1, altura, ancho , Amc, 0))
    else:
        if(elemDistintos(elemAltura)): 
            Amc[i] = (res2 , True)
            if(i == 0):
                return res2
            else:
                return max(res2 , mayorEmpinado(i - 1 , altura, ancho , Amc))


def elemDistintos(elemAltura):
    for k in range(1 , len(elemAltura)):
        if(elemAltura[0] != elemAltura[k]):
            return False
    return True    

def menorEmpinado(i , altura , ancho , Amd):
    elemAltura = [altura[i]]
    j = i + 1
    res1 = altura[i]
    res2 =  altura[i]
    yaCalculado = False

    while(j < len(altura) and altura[j] <= altura[i]):
        if(Amd.get(j)[0] != None and (Amd.get(j) == True or altura[j] != altura[i])):
            res1 = res2 + Amd.get(j)
            yaCalculado = True
            j = j + 1
        else:
            elemAltura = elemAltura.append(altura[j]) 
            res2 = res2 + ancho[j]
            j = j + 1
    if(yaCalculado):
        Amd[i] = (res1 ,True)
        if(i == 0):
            return res1
        else:
            return max(res1 , mayorEmpinado(i - 1, altura, ancho , Amd))
    else:
        if(elemDistintos(elemAltura)): 
            Amd[i] = (res2 , True)
            if(i == 0):
                return res2
            else:
                return max(res2 , mayorEmpinado(i - 1 , altura, ancho , Amd))

if __name__ == "__main__":
    main()