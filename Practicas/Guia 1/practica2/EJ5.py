def subset_sum(C, k):
    n = len(C)
    # Inicializar la matriz M
    M = [[False] * (k + 1) for _ in range(n + 1)]
    
    # Paso 2: Inicializar M[0, j]
    for j in range(k + 1):
        M[0][j] = (j == 0)
    
    # Paso 3 y 4: Calcular M[i, j] para todo 1 ≤ i ≤ n y 0 ≤ j ≤ k
    for i in range(1, n + 1):
        for j in range(k + 1):
            print(i , j)
            print(M)
            M[i][j] = M[i - 1][j] or (j - C[i - 1] >= 0 and M[i - 1][j - C[i - 1]])
            print(M[i][j])
            
    # Retornar el resultado M[n][k]
    return M[n][k]

# Ejemplo de uso
C = [1, 2, 3, 7]
k = 6
resultado = subset_sum(C, k)
print("¿Se puede obtener la suma", k, "a partir del conjunto", C, "?", resultado)


def subset_sume(C, k):
    n = len(C)
    # Inicializar las dos filas de la matriz M
    prev_row = [False] * (k + 1)
    current_row = [False] * (k + 1)

    # Paso 2: Inicializar M[0, j]
    prev_row[0] = True

    # Paso 3 y 4: Calcular M[i, j] para todo 1 ≤ i ≤ n y 0 ≤ j ≤ k
    for i in range(1, n + 1):
        for j in range(k + 1):
            current_row[j] = prev_row[j] or (j - C[i - 1] >= 0 and prev_row[j - C[i - 1]])
        # Actualizar prev_row con los valores de current_row
        prev_row = current_row[:]
    
    # Retornar el resultado current_row[k]
    return current_row[k]

# Ejemplo de uso
C = [1, 2, 3, 7]
k = 6
resultado = subset_sume(C, k)
print("¿Se puede obtener la suma", k, "a partir del conjunto", C, "?", resultado)
