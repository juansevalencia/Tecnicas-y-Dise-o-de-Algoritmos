//M[0][0]

m(i , j, A){
    if(i == n && j == n -1 ){
        return 0;
    }else{
        if(i == n || j == n){
            return INF;
        }else{
            if(M[i][j] == -1){
                res = min(m(i + 1 , j) , m(i, j + 1));
                res -= A[i][j]
                if(res <= 0){
                    res = 1; //si es menor o a igual a 0 cosa que no hace falta darle vida de mas
                }
                M[i][j] = res;
            }
            return M[i][j];
        }   
    }
}

mBU(n , m , A){
if( m < n){
    vector<int> V (m + 1 , INF); //menor cantidad de columnas
    V[m] = 0; //solo se usa en la primera iteraicon
    for (int i = n - 1 , i>= 0    , i--){
        for (int j = m -1 , j >= 0 , j--){ 
            if(i < n - 1 && j == m - 1){
                a = INF;
            }else{    
                a = V[j + 1]
            }
            res = min(a, V[j]) - A[i][j];
            if(res <= 0){
                V[j] = 1; 
            }else{
                V[j] = res;
            }
        }
    }
    return V[0];
}else{ //menor cantidad de filas o igual
    vector<int> V (n + 1, INF);
    for(int j = n - 1 ; j >= 0 ; j -- ){
        for(int i = m - 1, i >= 0 ; i --){
            if(j == n -1 && i < m - 1){
                a = INF
            }else{
                a = v[i + 1]
            }
            int res = min(V[i] , a ) - A[j][i];
            
        }
    }
}

}
