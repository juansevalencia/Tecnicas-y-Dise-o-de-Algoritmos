def main():
    res = []
    entrada = int(input())
    while(entrada != 0):
        cant_personas = entrada
        personas = list(map(int, input().split()))
        min_cant = 0
        for p in range(0, cant_personas - 1): #el ultimo no
             ##por enunciado asumimos que siempre se cubren todos
            min_cant += abs(personas[p]) #greedy, mandaselo al siguiente con ese costo
            personas[p + 1] += personas[p]
        res.append(min_cant) #cuak
        entrada = int(input()) #lee la sig 
    for r in res:
        print(r)
main()