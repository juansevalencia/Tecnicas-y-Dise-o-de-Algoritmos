def main(casas, datos_casas):
    res = []
    global datos
    global result 
    cant_casas = casas
    datos = datos_casas
    while cant_casas != 0:
        result = 0
        minimo_costo(cant_casas)
        res.append(result)
        cant_casas = int(input())        

    for i in range(0, len(res)):
        print(res[i])

def minimo_costo(cant_casas):
    global datos
    global result
    i = 0
    while i < cant_casas - 1:
        if datos[i] > 0:
            buscarVendedor(i,i+1)
        else:
            buscarComprador(i , i+1)
        i = i + 1    

def buscarComprador(i , j):
    global datos
    global result
    if datos[j] > 0:
        if abs(datos[i]) < datos[j]:
            result += (j-i)*abs(datos[i])
            datos[j] = datos[i] + datos[j]
            datos[i] = 0
            return
        else:
            if abs(datos[i]) > datos[j]:
                result += (j- i)*(datos[j])
                datos[i] = datos[j] + datos[i] 
                datos[j] = 0 
                buscarComprador(i, j + 1)
            else:
                if abs(datos[i]) == datos[j]:
                    result += (j-i)*(abs(datos[i]))
                    datos[i] = 0
                    datos[j] = 0
                else:
                    None           
    else:
        buscarComprador(i,j + 1)

def buscarVendedor(i,j):
    global datos
    global result
    if datos[j] < 0:
        if abs(datos[j]) < datos[i] :
            result += (j - i)*(abs(datos[j]))
            datos[i] = datos[i] + datos[j]
            datos[j] = 0
            buscarVendedor(i , j+1)
        else:
            if abs(datos[j]) > datos[i]:
                result += (j-i)*(datos[i])
                datos[j] = datos[j] + datos[i] 
                datos[i] = 0                 
            else:
                if abs(datos[j]) == datos[i]:
                    result += datos[i]
                    datos[i] = 0
                    datos[j] = 0       
                else:
                    None  
    else:
        buscarVendedor(i,j + 1)

# Uso de la función main() con datos proporcionados como argumentos
casas = 6
datos_casas = [-1000, -1000, -1000, 1000, 1000 , 1000]
main(casas, datos_casas)