#include <bits/stdc++.h>

using namespace std;

#define INF 99999

int main(){
    int n;
    cin >> n;
    cin.ignore();

    vector<int> adj[n];

    unordered_map<int,bool> esta_presente;
    
    vector<int> distancias[n];

    vector<int> inf(n, INF);
    
    for(int i = 0 ; i < n ; i++){
        vector<int> actual;
        string linea;
        getline(cin, linea);
        stringstream ss(linea);
        int numero;

        while(ss >> numero){
            actual.push_back(numero);
        }
        adj[i] = actual;

        esta_presente[i] = false; //niguno empieza presente
    }
    
    //ultima linea

    vector<int> orden_inverso;
    string linea;
    getline(cin , linea);
    stringstream ss(linea);
    int numero;

    while(ss >> numero){
        orden_inverso.push_back(numero-1);
    }

    if(n == 1){
        cout << 0;
        return 0;
    }

    vector<int> suma_distancias(n,0);
    //a medida que se va agrandando la matriz, voy completando la suma de las distancias, ya que con la forma que yo quiero hacerlo se me va a n⁴.


    for(int i = n-1 ; i >= 0 ; i--) {
        int v_true = orden_inverso[i];
        esta_presente[v_true] = true;
        
        for(int x = 0 ; x < n ; x++){
            for(int y = 0 ; y < n ; y++){
                if(x!= y && adj[x][y] > adj[x][v_true] + adj[v_true][y]){ //verifico si el vertice v_true que se esta teniendo en cuenta como nuevo mejora mi distancia
                    adj[x][y] = adj[x][v_true] + adj[v_true][y];
                    
                }
            }
        }

        for(int it = 0 ; it < n ; it++){
            for(int it2 = 0 ; it2 < n ; it2++){
                if(adj[it][it2] != INF && esta_presente[it] && esta_presente[it2]){
                    suma_distancias[v_true] += adj[it][it2];
                }
            } 
        }
        
    }

    for(int i = 0 ; i < n ;i++ ){
        cout << suma_distancias[orden_inverso[i]] << " ";
    }

    return 0;
}