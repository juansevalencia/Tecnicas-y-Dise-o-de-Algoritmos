def CETD(i , j , cortes ):
    matriz =[[None] * (j + 1)  for _ in range(j + 1)] ## O(jxj)
    return CETDAux(i , j , cortes , matriz)

def CETDAux(i , j , cortes , matriz):
    print(i , j )
    print(matriz )
    print(noHayCortes(i , j , cortes))
    if ((i == j - 1) or (noHayCortes(i , j , cortes))):
        return 0
    else:
        if(matriz[i][j] == None):
            matriz[i][j] = j - i + minJ(i , j , cortes , matriz)
        return matriz[i][j]
    
def minJ(i , j , cortes ,matriz):
    ms = 10^5
    for c in cortes:
        cortesmenosc = []
        for k in cortes: ##O(C)
            if(k != c):
                cortesmenosc.append(k)    
        if(i<c< j ):
            sp = min((j - i  + CETDAux(i , c , cortesmenosc , matriz)), (j - i  + CETDAux(c , j, cortesmenosc , matriz)))
            print(sp)
            if( ms > sp):
                ms = sp
    return ms

def noHayCortes(i , j , cortes):
    for c in cortes: 
        if(i<c < j):
            return False
    return True 


def ant(cortesaux , c ):
    i = 0
    while(cortesaux[i+1] != c):
        i = i + 1
    return cortesaux[i]    

def sig(cortesaux , c):
    i = 0
    while(cortesaux[i]!= c):
        i = i + 1
    return cortesaux[i+1]            


##va a ser la longitud de lo que lo encierra. la longitud de Lo que lo encierre mas cerca ya sea pared o corte 
            
           
resultado = CETD( 10 , [2 , 4 , 7])
print(resultado)