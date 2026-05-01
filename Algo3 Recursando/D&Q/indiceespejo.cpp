def indiceEspejo(a, i, j):
    if i > j:
        return False
    
    k = (i + j) // 2
    
    # Comprobamos si hay un índice espejo
    if a[k] == k:
        return True
    elif a[k] > k:
        # Si a[k] > k, significa que cualquier índice espejo debe estar a la izquierda
        return indiceEspejo(a, i, k - 1)
    else:
        # Si a[k] < k, significa que cualquier índice espejo debe estar a la derecha
        return indiceEspejo(a, k + 1, j)

# Función principal
def tieneIndiceEspejo(a):
    return indiceEspejo(a, 0, len(a) - 1)

	
//f(n) = theeta(n^log_2-1) = O(N)  
//T(n/2) + f(n) = O(log n)
