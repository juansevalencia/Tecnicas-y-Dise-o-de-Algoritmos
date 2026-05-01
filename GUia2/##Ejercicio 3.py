##Ejercicio 3

def potenciaLogaritmica(a , b):
    if(a  == 0 ):
        return 1
    else:
        if(a % 2 == 0):
            b = potenciaLogaritmica(a , b-1)
            return b*b 
        else:
            b = potenciaLogaritmica(a, b - 1 )
            return a*b*b
        