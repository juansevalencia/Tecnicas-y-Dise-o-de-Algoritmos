#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Prototipo de la función
int mgn(int c, int j, vector<vector<int>>& M, const vector<int>& precio);

int main() {
    int n; // Cantidad de días
    cout << "Introduce la cantidad de días: ";
    cin >> n;

    // Cantidad de asteroides
    int c;
    cout << "Introduce la cantidad de asteroides: ";
    cin >> c;

    // Vector de precios
    vector<int> precio(n);
    cout << "Introduce los precios de los asteroides: ";
    for (int i = 0; i < n; i++) {
        cin >> precio[i];
    }

    // Matriz para memorizar resultados
    vector<vector<int>> M(c + 1, vector<int>(n + 1, -1));

    // Inicializamos el caso base
    for (int i = 0; i <= c; i++) {
        M[i][0] = 0; // Si no hay días, no hay ganancias
    }

    // Llamada a la función
    int resultado = mgn(0, n, M, precio);
    cout << "La ganancia máxima es: " << resultado << endl;

    return 0;
}

// Función para calcular la ganancia máxima
int mgn(int c, int j, vector<vector<int>>& M, const vector<int>& precio) {
    // Casos base
    if (c > j || c < 0) {
        return -999999; // Caso inválido
    }
    if (j == 0) {
        return 0; // Sin días, sin ganancias
    }

    // Comprobar si ya se ha calculado este subproblema
    if (M[c][j] == -1) {
        // Cálculos de las posibles ganancias
        int res1 = mgn(c - 1, j - 1, M, precio) - precio[j - 1]; //es menos 1 para poder acceder solamente.
        int res2 = mgn(c + 1, j - 1, M, precio) + precio[j - 1];
        int res3 = mgn(c, j - 1, M, precio);

        // Guardamos el resultado máximo
        M[c][j] = max({res1, res2, res3});
    }

    return M[c][j];
}
