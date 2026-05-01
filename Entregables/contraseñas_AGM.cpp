#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

int min_entre_ir_para_atras_o_adelante(string c1, string c2) {
    int res = 0;
    for (int i = 0; i < 4; i++) {
        res += min(abs(c1[i] - c2[i]), 10 - abs(c1[i] - c2[i]));
    }
    return res;
}

int prim(const vector<vector<pair<int, int>>>& adj_list, int n) {
    int res = 0;
    int i = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> queue;
    vector<bool> visitados(n, false); 
    
    queue.emplace(0, 0);
    while (i < n) {
        int a = queue.top().second;
        int costo = queue.top().first;
        queue.pop();

        if (!visitados[a]) {
            visitados[a] = true;
            res += costo;
            for (int j = 0; j < adj_list[a].size(); ++j) {
                queue.emplace(adj_list[a][j].second, adj_list[a][j].first);
            }
            i++;
        }
    }
    return res;
}

int main() {
    int casos;
    cin >> casos;

    while (casos > 0) {
        string cer0 = "0000";
        int masCerca = numeric_limits<int>::max();
        
        int cant_contraseñas;
        cin >> cant_contraseñas;

        vector<string> contraseñas(cant_contraseñas); 
        int i = 0;
        while (i < cant_contraseñas) {
            cin >> contraseñas[i];
            masCerca = min(masCerca, min_entre_ir_para_atras_o_adelante(cer0, contraseñas[i]));
            i++;
        }
        vector<vector<pair<int, int>>> adj_list(cant_contraseñas);
        int c1 = 0;
        while (c1 < cant_contraseñas) {
            int c2 = c1 + 1;
            while (c2 < cant_contraseñas) {
                int costo = min_entre_ir_para_atras_o_adelante(contraseñas[c1], contraseñas[c2]);
                adj_list[c1].push_back(make_pair(c2, costo));
                adj_list[c2].push_back(make_pair(c1, costo));
                c2++;
            }
            c1++;
        }
        
        int res = prim(adj_list, cant_contraseñas);
        cout << masCerca + res << "\n";
        casos--;
    }
    return 0;
}
