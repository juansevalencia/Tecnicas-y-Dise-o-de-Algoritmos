#include <bits/stdc++.h>

int n;
vector<int> elegidos;
int numero_magico;


bool suma_columnas_no_supera_magic(int i , int j , int k , vector<vector<int>> *c){
    //verifica
    int cpy_k = k;
    for(int w = 0 ; w <= i ; w++){
        cpy_k += c[w][j];
    } 
    if(cpy_k < numero_magic ){
        return true;
    }
    return false;
}

bool suma_diagonales_no_supera_magic(int i , int j , int k , vector<vector<int>> *c){
    int cpy_k = k;
    i--;
    j--;
    while(i != -1 && j != -1){
        cpy_k +=c[i][j]  
    }
    if(cpy_k < numero_magic){ //puede ser que pifie agarrando un numero_magic viejo? Deberia agarrar uno para cada funcion y pasarlo como param no?
        return true;
    }
    return false;
}

int magicuadrados(int i , int j , vector<vector><int> c){
    if(i == n && j == n){
        return esCM(c);
    }
    if(j == n-1 ){
        for(int w = 0 ; w< n * n ; w++ ){
            bool pertenece = false;
            for(int k = 0 ;k < size(elegidos) ; k++){
                if(elegidos[k] == w){
                    pertenece = true;
                    break;
                }
            }    
            if(!pertenece){
                if(suma_filas_no_supera_magic(i , j ,k, c) && suma_columnas_no_supera_magic(k ,c) && suma_diagonales_no_supera_magic(k ,c )){
                    c[i][j] = k;
                    esCM(i + 1 ; 0; c);          
                }
            }
        }
    }else{
        if(i == 1 && j == 0){
            numero_magico = 0;
            for(int w = 0 ; w< n ; n++){
                numero_magico += c[0][w];
            }
        }
        for(int w = 0 ; w< n * n ; w++ ){
            bool pertenece = false;
            for(int k = 0 ;k < size(elegidos) ; k++){
                if(elegidos[k] == w){
                    pertenece = true;
                    break;
                }
            }    
            if(!pertenece){
                if(suma_filas_no_supera_magic(k, c) && suma_columnas_no_supera_magic(k ,c) && suma_diagonales_no_supera_magic(k ,c )){
                    c[i][j] = k;
                    esCM(i + 1 ; 0; c);          
                }
            }
        }    
    }
    return 0; //cc
}

int main(){
    n = 3;
    elegidos = []
    return magicuadrados(0 ,0 , [[]]);
}

