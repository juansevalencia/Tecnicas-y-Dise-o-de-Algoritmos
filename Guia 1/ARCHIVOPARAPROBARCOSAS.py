T = int(input())
for caseNumber in range(1, T +1):
    jugadores = []
    cualidades = {}
    for i in range(10):
        nombre , ataque , defensa = input().split()
        jugadores.append(nombre)
        cualidades[nombre] = {'ataque':int(ataque) , 'defensa':int(defensa) }
print(jugadores[0])
print(cualidades)