#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int mayorEmpinado(int i, vector<int>& altura, vector<int>& ancho, vector<vector<int>>& Amc, int k) {
    if (i < 0) return 0;
    if (Amc[i][k] != -1) return Amc[i][k];
    else {
        if (altura[i] >= k)
            Amc[i][k] = mayorEmpinado(i - 1, altura, ancho, Amc, k);
        else
            Amc[i][k] = max(ancho[i] + mayorEmpinado(i - 1, altura, ancho, Amc, altura[i]), mayorEmpinado(i - 1, altura, ancho, Amc, k));
    }
    return Amc[i][k];
}

int menorEmpinado(int i, vector<int>& altura, vector<int>& ancho, vector<vector<int>>& Amd, int k) {
    if (i < 0) return 0;
    if(k == -1){ 
        return menorEmpinado(i , altura , ancho, Amd ,0);
    }    
    if (Amd[i][k] != -1 ) return Amd[i][k];
    else {
        if (altura[i] <= k){
            Amd[i][k] = menorEmpinado(i - 1, altura, ancho, Amd, k);
        }    
        else{
            Amd[i][k] = max(ancho[i] + menorEmpinado(i - 1, altura, ancho, Amd, altura[i]), menorEmpinado(i - 1, altura, ancho, Amd, k));
        }
    }
    return Amd[i][k];
}

pair<int, int> calcularEmpinados(int cantEdificios, vector<int>& altura, vector<int>& ancho) {
    vector<vector<int>> nones(cantEdificios + 1, vector<int>(*max_element(altura.begin(), altura.end()) + 2, -1));
    vector<vector<int>> none2(cantEdificios + 1, vector<int>(*max_element(altura.begin(), altura.end()) + 2, -1));
    int mayor = mayorEmpinado(cantEdificios - 1, altura, ancho, nones, *max_element(altura.begin(), altura.end()) + 1);
    int menor = menorEmpinado(cantEdificios - 1, altura, ancho, none2, *min_element(altura.begin(), altura.end()) - 1);
    return make_pair(mayor, menor);
}

int main() {
    int cantidadCasos;
    cin >> cantidadCasos;

    vector<pair<int, int>> resf;
    for (int ncaso = 1; ncaso <= cantidadCasos; ++ncaso) {
        int cantEdificios;
        cin >> cantEdificios;
        vector<int> altura(cantEdificios);
        vector<int> ancho(cantEdificios);
        for (int i = 0; i < cantEdificios; ++i)
            cin >> altura[i];
        for (int i = 0; i < cantEdificios; ++i)
            cin >> ancho[i];

        pair<int, int> nueva = calcularEmpinados(cantEdificios, altura, ancho);
        resf.push_back(nueva);
    }

    for (int k = 0; k < resf.size(); ++k) {
        if (resf[k].first >= resf[k].second)
            cout << "Case " << k + 1 << ". Increasing (" << resf[k].first << "). Decreasing (" << resf[k].second << ")." << endl;
        else
            cout << "Case " << k + 1 << ". Decreasing (" << resf[k].second << "). Increasing (" << resf[k].first << ")." << endl;
    }

    return 0;
}
