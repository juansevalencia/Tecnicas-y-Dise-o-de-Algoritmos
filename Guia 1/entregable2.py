def main():
    cantidadCasos = int(input())
    resf = []
    for ncaso in range(1 , cantidadCasos + 1):
        cantEdificios = int(input())
        altura = list(map(int , input().split()))
        ancho = list(map(int , input().split()))
        nones = [[None for _ in range(alturaMax(altura) + 2)] for _ in range(cantEdificios + 1)]
        none2 = [[None for _ in range(alturaMax(altura) + 2)] for _ in range(cantEdificios + 1)]
        maior = mayorEmpinado(cantEdificios - 1, altura ,ancho, nones , alturaMax(altura) + 1)
        menior = menorEmpinado(cantEdificios - 1 , altura ,ancho, none2, alturaMen(altura) - 1 )
        nueva = (maior , menior)
        print(menior)
        resf.append(nueva) #chequear que pasa si son iguales :0

    for k in range(0 , len(resf)):
        if(resf[k][0] >= resf[k][1] ):
            print("Case ", k + 1 ,". Increasing (" ,resf[k][0], "). Decreasing (" ,resf[k][1], ")." )
        else:
            print("Case ", k + 1 ,". Decreasing (" ,resf[k][1], "). Increasing (" ,resf[k][0], ")." )

    
def mayorEmpinado(i , altura ,ancho, Amc, k ):
    if( i < 0):
        return 0
    if(Amc[i][k] != None):
        return Amc[i][k]
    else:
        if(altura[i]>= k ):
            Amc[i][k] = mayorEmpinado(i - 1 , altura , ancho , Amc , k) ## otra rama se va a encargar de calcularlo para ese
        else:
            Amc[i][k] = max( ancho[i] + mayorEmpinado(i - 1 , altura , ancho , Amc , altura[i]) , mayorEmpinado(i - 1 , altura , ancho , Amc , k))  
    return Amc[i][k] 


def menorEmpinado(i , altura , ancho , Amd , k):
    if( i < 0):
        return 0
    if(i == 220):
        print("i", i , k )
        print(Amd[i][k]) 
    if(Amd[i][k] != None):
        return Amd[i][k]
    else:
        if( altura[i] <= k):
            Amd[i][k] = menorEmpinado(i - 1 , altura , ancho , Amd , k) ## otra rama se va a encargar de calcularlo para ese
        else:
            Amd[i][k] = max( ancho[i]+ menorEmpinado(i - 1 , altura , ancho , Amd , altura[i]) , menorEmpinado(i - 1 , altura , ancho , Amd , k))  
    return Amd[i][k] 


def alturaMax(lista):
    max = lista[0]
    for i in range(1 , len(lista)):
       if(max < lista[i]):
           max = lista[i]
    return max       

def alturaMen(lista):
    men = lista[0]
    for i in range(1 , len(lista)):
        if(men > lista[i]):
            men = lista[i]
    return men        

if __name__ == "__main__":
    main()