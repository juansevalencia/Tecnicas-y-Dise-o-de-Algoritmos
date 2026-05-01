int generar(M ;(i ;j)){
    if(i == n && j == n){
        if(esCuadradoMagico(M)){
            return 1;           
        }else{
            return 0;
        }
    }else{
        for (int k = 0; k <= n && noEsta(M; k) && ;k ++ ){
            generar(M[i][j]<-k ;sig(i:j))
        }
    } 
}

bool esCuadradoMagico(M: int[][]){
    return (SumaFilas(M) == SumaColumnas(M) == SumaDiagonales(M));
}

//chequea si las filas suman lo mismo ,que compare todas las sumas y si es true que devuelva el numero.

int SumaFilas(M: int[][]){
    if() 
}

int SumaFila (M: int[][]; int k){
    int resM = 0;
    for(int i = 0; i < M[k].longitud ; i++){
        resM += [k][i];
    }
    return resM
}

//lo mismo con sumacolumnas y suma diagonales


int noEsta(M  ; k){
    //que verifique si ya pusieron el numero.
}

//Quiero verificar si va cumpliendo con el numero por donde va? es necesario? Y solo con las filas porque la comlumna hasta qur no llegue no va

bool vaCumpliendoLaFila(M ; k){
    
}