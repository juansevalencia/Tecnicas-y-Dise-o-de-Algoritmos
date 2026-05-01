INF = 10**9
p = [3 , 5 , 2 , 7 , 8]
memo = [[-1] * len(p) for _ in range(len(p))]

# Top Down
# j = dias
# c = cantidad de asteroides , O(len(p) x len(p)) , complejidad espacial = O(len(P)x len(p))
def mgn(j, c):
    if c < 0 or c > j:
        return -INF
    if j == 0:
        return 0
    if memo[j - 1][c] == -1:
        no_operar = mgn(j - 1, c)
        comprar = mgn(j - 1, c - 1) - p[j - 1]
        vender = mgn(j - 1, c + 1) + p[j - 1]
        memo[j - 1][c] = max(vender, max(comprar, no_operar))
    return memo[j - 1][c]

#



def mgnBUatpad(c):
    n = len(p)
    m = [[0]* len(p) for _ in range(len(p))]
    for i in range(1, n+1):
        for j in range(1 ,c+1):
            comprar = m[i- 1][j - 1] - p[j]
            if(c< n ):
                vender = m[i - 1][j+1] + p[j]
            else:
                vender = -INF    
            pasar = m[i-1][j]
        m[i][j] = max(vender , comprar , pasar) 
    return m[n][c]


             
             