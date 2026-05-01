def main():
    t = int(input())
    for i in range(1 , t+1):
        cantidadArboles , altura , costoDeSalto = input().split() #bien
        valores = [[0 for _ in range(int(cantidadArboles))] for _ in range(int(altura))] ##la iesima altura va a ser i menos 1
        for j in range(0, int(cantidadArboles)):
            lineaEntera = list(map(int, input().split()))
            for i in range(1, lineaEntera[0]+1):
                valores[int(altura) -lineaEntera[i]][j] = valores[int(altura) -lineaEntera[i]][j] + 1 
                ##asi esta tal cual al mapita del ejercicio , ver dibujo 
        print(valores)        


        
if __name__ == "__main__":
    main()
