#include <limits>
#include <iostream>
#include <vector>
using namespace std;

vector<int> lista;

int msp(int bl,int n, int i, int cant_numeros, vector<vector<vector<int>>>& M){
    if(i == cant_numeros){
        return 0;
    }else{
        int res;
        if(M[bl][n][i] == -1){  
            if(lista[i] <= lista[n] && lista[i] >= lista[bl]){
                res = 1 + msp(bl, n , i+1, cant_numeros, M);
            }else{
                if((lista[i] <= lista[n])){ //no puedo elegir negro
                    int a = msp(i, n, i+1, cant_numeros , M);
                    int b = (msp(bl, n , i+1, cant_numeros , M) + 1);
                    res = min(a, b);
                }else{
                    if(lista[i] >= lista[bl]){  //no puedo elegir blanco
                        int a2 = msp(bl, i , i+1, cant_numeros , M); 
                        int b2 = 1 + msp(bl , n,i+1,cant_numeros , M);
                        res = min(a2, b2);
                    }else{ //puedo elegir cualquiera
                        int a3 = msp(bl, i, i+1, cant_numeros , M);
                        int b3 = msp(i, n, i+1, cant_numeros , M);
                        int c3 = 1 + msp(bl, n, i+1, cant_numeros , M);
                        res = min(a3, min(b3 , c3));
                    }
                }        
            }
            M[bl][n][i] = res;
        }
        return M[bl][n][i];
    }
} 

int main(){
    vector<int> result;
    int cant_numeros;
    cin >> cant_numeros;
    int j = 0;
    while(cant_numeros != -1){
        result.resize(result.size() + 1);

        vector<vector<vector<int>>> listaDeMatrices(cant_numeros + 3, vector<vector<int>>(cant_numeros + 3 , vector<int>(cant_numeros + 3, -1)));
        lista.resize(cant_numeros + 2);

        for(int i = 0; i < cant_numeros ; i++){
            cin >> lista[i];
        }
        lista[cant_numeros] = 9999999;
        lista[cant_numeros + 1] = -1;
        result[j] = msp(cant_numeros, cant_numeros +1, 0, cant_numeros, listaDeMatrices);
        cin >> cant_numeros;
        j++;
    }

    for ( int k = 0 ; k < result.size() ;k++){
        cout << result[k] << endl;
    }

    return 0;
}
