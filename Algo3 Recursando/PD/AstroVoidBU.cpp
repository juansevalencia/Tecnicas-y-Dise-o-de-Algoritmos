#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int mgnBU(int n, const vector<int>& precios) {
    // Crear un vector de memoización
    vector<int> memo(n + 1, 0);

    // Iterar sobre los días
    for (int i = 1; i <= n; i++) {
        // Iterar sobre las posiciones posibles
        for (int j = 0; j <= n - i; j++) {
            int k = (j == 0) ? -1 : memo[j - 1];

            // Calcular la ganancia máxima en la posición actual
            memo[j] = max({memo[j] , (j + 1 <= n ? memo[j + 1] + precios[j-1] : 0), k - precios[j- 1]}); 

            // Mostrar el estado actual del vector memo
            cout << "Estado de memo después de i=" << i << ", j=" << j << ": ";
            for (int m = 0; m <= n; m++) {
                cout << memo[m] << " ";
            }
            cout << endl; // Nueva línea después de cada estado
        }
    }

    return memo[0]; // Retornar la ganancia máxima
}

int main() {
    int n;
    cout << "Introduce la cantidad de días: ";
    cin >> n;

    vector<int> precios(n);
    cout << "Introduce los precios: ";
    for (int i = 0; i < n; i++) {
        cin >> precios[i];
    }

    int resultado = mgnBU(n, precios);
    cout << "La ganancia máxima es: " << resultado << endl;

    return 0;
}
