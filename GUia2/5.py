
def sumaDePotencias(A, n):
    matriz_res = A
    arrastrador = A
    i = 1
    while (i != n +1 ): #O(n) veces
        arrastrador = matrix_multiply(arrastrador ,A) #O(n³)
        matriz_res = matrix_sum(matriz_res, arrastrador) #O(n²)
        i = i + 1
    return matriz_res


def matrix_multiply(A, B):
    """
    Multiplica dos matrices A y B y devuelve el resultado.
    
    Parámetros:
        A (list): Matriz A representada como una lista de listas.
        B (list): Matriz B representada como una lista de listas.
        
    Devolución:
        list: Matriz resultante de la multiplicación.
    """
    rows_A = len(A)
    cols_A = len(A[0])
    rows_B = len(B)
    cols_B = len(B[0])
    
    # Verificar si las dimensiones son compatibles para la multiplicación
    if cols_A != rows_B:
        raise ValueError("Las dimensiones de las matrices no son compatibles para la multiplicación.")
    
    # Inicializar la matriz resultante con ceros
    result = [[0 for _ in range(cols_B)] for _ in range(rows_A)]
    
    # Multiplicar matrices
    for i in range(rows_A):
        for j in range(cols_B):
            for k in range(cols_A):
                result[i][j] += A[i][k] * B[k][j]
    
    return result


def matrix_sum(A, B):
    """
    Suma dos matrices A y B y devuelve el resultado.
    
    Parámetros:
        A (list): Matriz A representada como una lista de listas.
        B (list): Matriz B representada como una lista de listas.
        
    Devolución:
        list: Matriz resultante de la suma.
    """
    # Verificar si las dimensiones son iguales para la suma
    if len(A) != len(B) or len(A[0]) != len(B[0]):
        raise ValueError("Las dimensiones de las matrices no son iguales para la suma.")
    
    # Inicializar la matriz resultante con ceros
    result = [[0] * len(A[0]) for _ in range(len(A))]
    
    # Sumar matrices
    for i in range(len(A)):
        for j in range(len(A[0])):
            result[i][j] = A[i][j] + B[i][j]
    
    return result

A = [[1, 2, 3, 4],
     [5, 6, 7, 8],
     [9, 10, 11, 12],
     [13, 14, 15, 16]]
n = 8  # Suponiendo que n = 2^3 = 8
result = sumaDePotencias(A, n)
print(result)