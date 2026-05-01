import sys
def n_reinas(n):
    ##me dice que existe un tablero nxn y tengo que colocar la mayor cantidad de reinas de manera que no se choquen
    res = [-1 for _ in range(n)] ##creamos un vector de n posiciones. La posición 1 va indicar en la columna 1 en que fila vamos a poner la reina.
    ##esto es porque de base porque no pueden coinciidir en columnas van a ser todas distintias. No hace falta armar una matriz
    #también todos los numeros van a tener que ser distintos. POrque no puedne estar dentro de una misma fila dos reinas
    print(rec_n_reinas(res, 0, n, 0))

def rec_n_reinas(tabla, k, n, acum):
    # Caso base: si k alcanza n, hemos encontrado una solución completa
    if k == n:
        return acum
    
    # Recursión para explorar todas las opciones en la fila k
    max_acum = acum
    for i in range(n):
        if isSafe(tabla, k, i):
            tabla[k] = i  # Colocar una reina en la fila k, columna i
            max_acum = max(max_acum, rec_n_reinas(tabla, k + 1, n, acum + 1))
            tabla[k] = -1  # Deshacer la colocación para explorar otras opciones
    
    # Recursión para pasar a la siguiente fila sin colocar ninguna reina en la fila k
    max_acum = max(max_acum, rec_n_reinas(tabla, k + 1, n, acum))
    
    return max_acum
                


def isSafe(cpy_res ,k , i):
    ##chequea si no hay ninguno igual en valor a k
    for s in range(0 , k):
        if(cpy_res[s] == i):
            return False
        #chequea si no hay niguno en la diagonal
    for j in range(1,k):
        if(cpy_res[k - j] - j == cpy_res[k] or cpy_res[k - j] + j == cpy_res[k]):
            return False
    return True
                
n_reinas(3)