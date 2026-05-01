##primero tomemos los datos.
def min_pasos_contraseña():
    ##diagrama el grafo 
    vertices = []
    aristas = {}
    costo = {}
    for x1 in range (0,10):
        for x2 in range(0,10):
            for x3 in range(0,10):
                for x4 in range(0,10):
                    num_original = x1*1000 + x2*100 + x3*10 + x4
                    vertices + num_original
                    num = [x1, x2 , x3 , x4]
                    list = []
                    for k in range(0, 5): ##intuyo que no incluye al 5
                        cpy_num = num
                        cpy_num[k] += 1
                        cpy_num[k] = cpy_num[k] % 9 ##queremos que s e mueva de 0 a 9
                        res = cpy_num[0]*(1000) + cpy_num[1]*100 + cpy_num[2]*10 + cpy_num[3]
                        costo[(num_original,res)] = 1
                        costo[(res,num_original)] = 1
                        list + res
                        cpy_num2 = num
                        cpy_num2[k] -= 1
                        cpy_num2[k] = cpy_num[k] % 9
                        res2 = cpy_num2[0]*(1000) + cpy_num2[1]*100 + cpy_num2[2]*10 + cpy_num2[3]
                        costo[(num_original,res2)] = 1
                        costo[(res2,num_original)] = 1
            ##todas las aristas tienen que tener costo 1
                        list + res2
                    aristas[num_original] = list ##intuyo que no hace falta la vuelta ya que cuando pase por el numero lo va hacer.
        ##ya tenemos el grafo. hagamos caso por caso y a medida que vayamos avanzando en un mismo caso agreguemos las aristas a contraseñas ya enconotradas. No nos olivdemos de sacarlas 
        casos = int(input())
        res = []
        for i in range(0, casos):
            linea = input().split()
            cant_contraseñas = int(linea[0])
            contraseñas = linea[1:]
            contraseñas_obtenidas = []
            iniciador = 0 ##0000
            ##acordate de cambiar la contraseña obtenida ahora como inciador.           
            ##que el inciador conecte con todas las contraseñas ant en costo 0
            for i in range(0, cant_contraseñas):
                for c in contraseñas_obtenidas:
                    aristas[iniciador] = aristas[iniciador] + i
                    costo[iniciador,i] = 0
                    aristas[i] = aristas[i] + iniciador
                    costo[i, iniciador] = 0
                Primm(iniciador) ##no





