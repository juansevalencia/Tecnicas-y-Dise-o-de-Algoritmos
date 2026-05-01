#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Suponemos que hay una función que determina si hay cortes disponibles
int cant_cortes(int i, int j, const vector<int>& cortes) {
    int count = 0;
    for (int c : cortes) {
        if (c > i && c < j) {
            count++;
        }
    }
    return count;
}

int buscar_min(const vector<int>& res) {
    int min_val = numeric_limits<int>::max();
    for (int val : res) {
        if (val < min_val) {
            min_val = val;
        }
    }
    return min_val;
}

int mc(int i, int j, const vector<int>& cortes, vector<vector<int>>& M) {
    if (cant_cortes(i, j, cortes) == 0) {
        return 0;
    }

    if (M[i][j] == -1) {
        vector<int> res;

        for (int c : cortes) {
            if (i < c && c < j) {
                res.push_back(mc(i, c, cortes, M) + mc(c, j, cortes, M));
            }
        }

        M[i][j] = (j - i) + buscar_min(res);

        // Mostrar cómo se llena la matriz
        cout << "M[" << i << "][" << j << "] = " << M[i][j] << endl;
    }
    
    return M[i][j];
}

void imprimirMatriz(const vector<vector<int>>& M) {
    cout << "Matriz de memoización:\n";
    for (const auto& fila : M) {
        for (int val : fila) {
            cout << val << "\t";
        }
        cout << endl;
    }
}

int main() {
    int longitud;
    cout << "Ingresa la longitud de la barra: ";
    cin >> longitud;

    int numCortes;
    cout << "Ingresa el número de cortes: ";
    cin >> numCortes;

    vector<int> cortes(numCortes);
    cout << "Ingresa las posiciones de los cortes: ";
    for (int i = 0; i < numCortes; i++) {
        cin >> cortes[i];
    }

    // Crear la matriz de memorization
    vector<vector<int>> M(longitud + 1, vector<int>(longitud + 1, -1));

    // Llamar a la función principal
    int resultado = mc(0, longitud, cortes, M);

    cout << "El costo mínimo de los cortes es: " << resultado << endl;

    // Imprimir la matriz de memoización final
    imprimirMatriz(M);

    return 0;
}
