#include <bits/stdc++.h>
using namespace std;
#define INF 9999999999LL

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<vector<long long>> adj(n, vector<long long>(n, INF));
    
    // Leer matriz de adyacencia
    for(int i = 0; i < n; i++) {
        adj[i][i] = 0; // Distancia a sí mismo es 0
        for(int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }
    
    // Leer orden inverso
    vector<int> orden_inverso(n);
    for(int i = 0; i < n; i++) {
        cin >> orden_inverso[i];
        orden_inverso[i]--; // Convertir a índice base 0
    }
    
    if(n == 1) {
        cout << 0;
        return 0;
    }
    
    vector<long long> suma_distancias(n, 0);
    vector<bool> esta_presente(n, false);
    
    // Floyd-Warshall con orden inverso
    for(int k = n-1; k >= 0; k--) {
        int v_true = orden_inverso[k];
        esta_presente[v_true] = true;
        
        // Floyd-Warshall
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                adj[i][j] = min(adj[i][j], adj[i][v_true] + adj[v_true][j]);
            }
        }
        
        // Calcular suma de distancias
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(esta_presente[i] && esta_presente[j]) {
                    suma_distancias[v_true] += adj[i][j];
                }
            }
        }
    }
    
    // Imprimir en el orden original
    for(int i = 0; i < n; i++) {
        cout << suma_distancias[orden_inverso[i]] << " ";
    }
    
    return 0;
}