#include <bits/stdc++.h>

using namespace std;

int mejorSuma;
int P;
int N;
vector<int> pesos;

void CDbt(int a, int i){
    if(i == N ){
        if (a > mejorSuma && a <= P) {
            mejorSuma = a;
        }   
    }else{
        CDbt(a , i + 1);
        CDbt(a + pesos[i], i + 1); 
    }
}

int main(){
    cin >> N >> P; //en cambio asi los espera de una.
    pesos.resize(N);
    for(int i = 0 ; i < N ; i++){
        cin >> pesos[i]; //cuando pasamos los argumentos por consola asi, espera separados linea por linea
    }
    mejorSuma = 0;
    CDbt(0, 0); 
    cout << mejorSuma << endl;
    return 0;
}