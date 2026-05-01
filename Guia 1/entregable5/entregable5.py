import sys

sys.setrecursionlimit(1_000_00)


def main():
    res = []
    global datos
    global result 
    cant_casas = int(input()) 
    while(cant_casas != 0  ):
        datos = [int(num) for num in input().split()]
        result = 0
        minimo_costo(cant_casas)
        res.append(result)
        cant_casas = int(input())        
    for k in range(0, len(res)):
        print(res[k])

def minimo_costo(cant_casas):
    r = 0
    while(r < cant_casas - 1 and noTodos0(datos) ): ##si hace falta meto un noTodos0 aca para datos
        if(datos[r] > 0):
            buscarVendedor(r,r+1)
        else:
            buscarComprador(r , r+1)
        r = r + 1    

def buscarComprador(i , j):
    global result
    global datos
    if(j< len(datos)):
        if(datos[j] > 0):
            print("i vendedor", i ,"su valor" , datos[i])
            print("j comprador", j ,"su valor" , datos[j])
            if(abs(datos[i]) < datos[j] ):
                x = (j-i)*abs(datos[i])
                result += x
                datos[j] = datos[i] + datos[j]
                datos[i] = 0
                print("datos:", datos)
                print("x", x)          
            else:
                if(abs(datos[i]) > datos[j]):
                    x = (j- i)*(datos[j])
                    result += x
                    datos[i] = datos[j] + datos[i] 
                    datos[j] = 0 
                    print("datos:", datos)
                    print("x", x)          
                    buscarComprador(i, j + 1)
                else:
                    if(abs(datos[i]) == datos[j]):
                        x = (j-i)*(abs(datos[i]))
                        result += x
                        datos[i] = 0
                        datos[j] = 0
                        print("datos:", datos)
                        print("x", x)          
                    else:
                        None                           
        else:
            buscarComprador(i,j + 1)

def buscarVendedor(i,j):
    global result
    global datos
    if(j < len(datos)):
        if(datos[j] < 0):
            print("i comprador", i , "su valor" , datos[i])
            print("j vendedor", j , "su valor" , datos[j])
            if(abs(datos[j]) < datos[i] ):
                x = (j - i)*(abs(datos[j]))
                result += x
                datos[i] = datos[i] + datos[j]
                datos[j] = 0
                print("datos:", datos)
                print("x", x)          
                buscarVendedor(i , j+1)
            
            else:
                if(abs(datos[j]) > datos[i]):
                    x = (j-i)*(datos[i])
                    result += x
                    datos[j] = datos[j] + datos[i] 
                    datos[i] = 0
                    print("datos:", datos)
                    print("x", x)          
                else:
                    if(abs(datos[j]) == datos[i]):
                        x = (j - i)*datos[i]
                        result += x
                        datos[i] = 0
                        datos[j] = 0
                        print("datos:", datos)                
                        print("x", x)                      
                    else:
                        None
        else:
            buscarVendedor(i,j + 1)

def noTodos0(datos):
    for i in datos:
        if(i != 0 ):
            return True
    return False        

main()
