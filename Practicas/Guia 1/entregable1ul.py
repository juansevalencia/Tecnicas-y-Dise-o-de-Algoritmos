def calcularDel(sp,ms,jugadores , posRestantes, cualidades):
    if(posRestantes == 0):
        ms = maxA(ms ,sp , cualidades)
    else:    
        if len(jugadores) < posRestantes:
            return ms
        else:    
            restante = jugadores[1:]
            sp1 = sp[:]  # Haciendo una copia de sp utilizando el operador de rebanado
            cuak = jugadores[0]
            sp1.append(cuak)
            sp = sorted(sp)
            sp1 = sorted(sp1)
            incluimos = calcularDel(sp1 , ms , restante , posRestantes-1 , cualidades)
            noIncluimos = calcularDel(sp , ms , restante , posRestantes, cualidades)
            ms =  maxA(noIncluimos , incluimos , cualidades)
    return ms 

def maxA(s0 , s1 , cualidades):
    if(s1 == []):
        return s0
    else:
        if(s0 == []):
            return s1
        else:
            sumA0 = 0
            i = 0
            while(i< len(s0)):
                sumA0 = sumA0 + cualidades[(s0[i])]['ataque']
                i +=1
            sumA1 = 0
            i = 0
            while(i < len(s1)):
                sumA1 = sumA1 + cualidades[(s1[i])]['ataque']   
                i += 1 
            ##print(sumA0)
            ##print(sumA1)    
            if(sumA0< sumA1):
                return s1
            else:
                if(sumA0>sumA1):
                    return s0
                else:
                    sumD0 = 0
                    for i in s0:
                        sumD0 = sumD0 + cualidades[i]['defensa']
                    sumD1= 0    
                    for i in s1:
                        sumD1 = sumD1 + cualidades[i]['defensa'] 
                    if(sumD0 < sumD1):
                        return s0
                    else:
                        if(sumD0 > sumD1):
                            return s1    
                        else:   
                            if(lexicoAntes(s0 , s1) == -1):
                                return s0
                            else:
                                return s1


def lexicoAntes(s0 , s1):
    comp = 0
    i = 0
    while(comp == 0):
        if s0[i] < s1[i]:
            comp = -1
        if s0[i] > s1[i]:
            comp = 1
        i = i+1
    return comp    

def main():
    t = int(input())
    resultados = []
    for caseNumber in range(1, t +1):
        jugadores = []
        cualidades = {}
        for i in range(10):
            nombre , ataque , defensa = input().split()
            jugadores.append(nombre)
            cualidades[nombre] = {'ataque':int(ataque) , 'defensa':int(defensa) }
        jugadores = sorted(jugadores)
        sp = []
        ms = []
        mejor_combinacion = calcularDel(sp,ms,jugadores ,5 , cualidades)
        defensores = [j for j in jugadores if j not in mejor_combinacion]
        defensores = sorted(defensores)
        resultadosA = []
        resultadosA.append(mejor_combinacion)
        resultadosA.append(defensores)
        resultados.append(resultadosA)
    i = 0
    while(i< len(resultados)):
        print("Case {}:".format(i+1))
        print("({})".format(", ".join(resultados[i][0])))    
        print("({})".format(", ".join(resultados[i][1])))
        i = i+1

if __name__ == "__main__":
        main()