##ej1
def izqDominante(arreglo, i , j):
    if(j - i  == 1):
        return True
    return suma(arreglo , i , j // 2 ) and suma(arreglo , j // 2 , j) and izqDominante(arreglo , i , j// 2 ) and izqDominante(arreglo , j//2 , j )

def suma()