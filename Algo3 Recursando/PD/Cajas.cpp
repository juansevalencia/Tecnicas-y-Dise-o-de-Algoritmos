#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Definir una constante para el valor infinito negativo
const int NEG_INF = numeric_limits<int>::min();

// Declaración de la función mcc
int mcc(int i, int j, const vector<int>& soporte, const vector<int>& peso, vector<vector<int>>& M, int n) {
    // Si el peso restante es negativo, no se pueden apilar más cajas
    if (j < 0) return NEG_INF;

    // Si hemos procesado todas las cajas o no queda peso, retornamos 0
    if (i == n || j == 0) return 0;

    // Si ya se ha calculado el resultado, lo retornamos
    if (M[i][j] == -1) {
        // Caso en el que se incluye la caja i
        int A = NEG_INF; // Inicializamos A a un valor negativo
        if (peso[i] <= j) { // Solo consideramos agregar la caja si cabe
            A = 1 + mcc(i + 1, min(j - peso[i], soporte[i]), soporte, peso, M, n);
        }

        // Caso en el que no se incluye la caja i
        int B = mcc(i + 1, j, soporte, peso, M, n);

        // Tomamos el máximo de ambos casos
        M[i][j] = max(A, B);
    }

    return M[i][j];
}

int main() {
    int n;
    cout << "Ingresa el número de cajas: ";
    cin >> n;

    vector<int> soporte(n);
    vector<int> peso(n);

    cout << "Ingresa los pesos de soporte de cada caja: ";
    for (int i = 0; i < n; i++) {
        cin >> soporte[i];
    }

    cout << "Ingresa los pesos de cada caja: ";
    for (int i = 0; i < n; i++) {
        cin >> peso[i];
    }

    // Definir el peso máximo
    int pesoMaximo;
    cout << "Ingresa el peso máximo que se puede soportar: ";
    cin >> pesoMaximo;

    // Crear la matriz de memoización
    vector<vector<int>> M(n + 1, vector<int>(pesoMaximo + 1, -1));

    // Llamar a la función principal
    int resultado = mcc(0, pesoMaximo, soporte, peso, M, n);

    if (resultado < 0) {
        cout << "No se pueden apilar cajas sin exceder el peso." << endl;
    } else {
        cout << "El número máximo de cajas que se pueden apilar es: " << resultado << endl;
    }

    return 0;
}
