#include <bits/stdc++.h>

int n;
vector<int> elegidos;

int magicuadrados(int i , int j , c){
    if(i == n && j == n){
        return esCM(c);
    }
    if(j == n-1){
        for(int i = 0 ; i< n * n ; i++ ){
            bool pertenece = false;
            for(int k = 0 ;k < size(elegidos) ; k++){
                if(elegidos[k] == i){
                    pertenece = true;
                    break;
                }
            }    
            if(!pertenece){
                c[i][j] = k;
                esCM(i + 1 ; 0; c);
            }
        }
    }else{
        for(int i = 0 ; i< n * n ; i++ ){
            bool pertenece = false;
            for(int k = 0 ;k < size(elegidos) ; k++){
                if(elegidos[k] == i){
                    pertenece = true;
                    break;
                }
            }    
            if(!pertenece){
                c[i][j] = k;
                esCM(i ; j + 1; c);
            }
        }    
    }
}

int main(){
    n = 3;
    elegidos = []
    return magicuadrados(0 ,0 , [[]]);
}