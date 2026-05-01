#include <limits>
#include <bits/stdc++.h>
using namespace std;#

numeric_limits<double> INF = infinity();
vector<int> lista;
int n;

int maximos_numeros_sin_pintar(int i, int bl, int ng){
    if(i == n){
        return 0;
    }else{
        if(lista[i] < bl && lista[i] > ng){
            return (1 + maximos_numeros_sin_pintar(i + 1, bl , ng));
        }else{
            if(lista[i] > bl && lista[i] > ng ){
                int a = min((1 + maximos_numeros_sin_pintar(i+1, bl ,ng) , maximos_numeros_sin_pintar(i+1, lista[i] , ng)) );
                return a;
            }else{
                if(lista[i] < bl && lista[i] < ng){
                    int b = min((1 + maximos_numeros_sin_pintar(i + 1,bl , ng)) , maximos_numeros_sin_pintar(i+1, bl, lista[i]));    
                    return b;
                }else{
                    int c = min({1 + maximos_numeros_sin_pintar(i + 1, bl ,ng),maximos_numeros_sin_pintar(i+1 , bl,lista[i] ) , maximos_numeros_sin_pintar(i+1, lista[i] , ng });
                    return c;
                }
            }
        }
    }
}

void main(){
    vector<int> result;
    int cant_numeros;
    cin >> cant_numeros;
    n = cant_numeros;
    int j = 0;
    while(cant_numeros != -1){
        lista.resize(cant_numeros);
        for(int i = 0; i < cant_numeros ; i++){
            cin >> lista[i];
        }
        result[j] = maximos_numeros_sin_pintar(0 , INF, -1);
    }
    j++;

}