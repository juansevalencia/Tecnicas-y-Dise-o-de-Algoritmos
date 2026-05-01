#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Función de verificación
bool f(int i, int vacasxasignar, vector<int>& B, int D, int ult, int cant_posiciones) {
    if (vacasxasignar == 0) {
        return true;
    } else if (i == cant_posiciones) {
        return false;
    } else {
        int qc = B[i];
        int qcy = B[i] - B[ult];
        if (qcy >= D) {
            return f(i + 1, vacasxasignar - 1, B, D, i, cant_posiciones);
        } else {
            return f(i + 1, vacasxasignar, B, D, ult, cant_posiciones);
        }
    }
}

int main() {
    int cant_casos;
    cin >> cant_casos;
    vector<int> resultfinal(cant_casos);

    for (int i = 0; i < cant_casos; ++i) {
        int cant_posiciones, cant_vacas;
        cin >> cant_posiciones >> cant_vacas;
        vector<int> B(cant_posiciones);

        for (int j = 0; j < cant_posiciones; ++j) {
            cin >> B[j];
        }

        sort(B.begin(), B.end());

        int low = 1;
        int high = B[cant_posiciones - 1] - B[0];
        int best = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (f(1, cant_vacas - 1, B, mid, 0, cant_posiciones)) {
                best = mid;  // Guardar el mejor resultado encontrado
                low = mid + 1;  // Intentar con un valor mayor
            } else {
                high = mid - 1;  // Intentar con un valor menor
            }
        }

        resultfinal[i] = best;
    }

    for (int t = 0; t < cant_casos; ++t) {
        cout << resultfinal[t] << endl;
    }

    return 0;
}

