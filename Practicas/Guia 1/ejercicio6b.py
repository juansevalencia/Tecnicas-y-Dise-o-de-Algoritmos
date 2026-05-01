def cc(billetes , i , c):
    memo = [[[ 999,999 ] for _ in range(c + 1)] for _ in range(len(billetes))] ##lo mejor aca seria poner un inf  , O(cantbilletes x c)
    return ccaux(billetes , i , c , memo)
##se puede decir que tiene complejidad O(cantidadbilletes x c)    
def ccaux(billetes, i, c , mem):
    print(mem)
    if i == len(billetes):
        return [999, 999]
    if(mem[i][c] != [999,999]):
        return mem[i][c]
    if c - billetes[i] <= 0:
        return  [billetes[i], 1] ##no tendria que devolver en memoria? pasa q aca estoy haciendo recursion
    else:
        mem[i][c] =  minAux([billetes[i] + ccaux(billetes, i + 1, c - billetes[i], mem)[0], 1 + ccaux(billetes, i + 1, c - billetes[i], mem)[1]]  , ccaux(billetes, i + 1, c, mem))
        return mem[i][c]
    
def minAux(a, b):
    if a[0] < b[0]:
        return a
    if a[0] > b[0]:
        return b
    if a[1] < b[1]:
        return a
    else:
        return b

def min_exceso_bu(B ,c):
    n =  len(c)
    memo = [[[9999, 9999]for _ in range(c + 1)] for _ in range(c)]
    memo[0][0] = [0, 0]
    for i in range(1, n + 1 ):
        for j in range(0 , c + 1 ):
            memo[i][j] = minAux(memo[i - 1][j] + [B[i - 1] , 1] , memo[i - 1][j])
            


def main():
    entrada = input("Ingrese los billetes que posee separados por espacios de menor a mayor: ")
    precio = int(input("Ingrese el costo: "))

    billetes = [int(x) for x in entrada.split()]
    
    result = min_exceso_bu(billetes, precio)
    print("Billete mínimo:", result[0])
    print("Cantidad de billetes:", result[1])

if __name__ == "__main__":
    main()

   




