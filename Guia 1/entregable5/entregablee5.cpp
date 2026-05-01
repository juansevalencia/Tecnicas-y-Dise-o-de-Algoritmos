#include <iostream>
#include <vector>
using namespace std;

vector<int> datos;
int result;

void minimo_costo(int cant_casas);
void buscarComprador(int i, int j);
void buscarVendedor(int i, int j);
bool noTodos0(const vector<int>& datos);

int main() {
    vector<int> res;
    int cant_casas;
    cin >> cant_casas;
    while (cant_casas != 0) {
        datos.clear();
        for (int i = 0; i < cant_casas; ++i) {
            int num;
            cin >> num;
            datos.push_back(num);
        }
        result = 0;
        minimo_costo(cant_casas);
        res.push_back(result);
        cin >> cant_casas;
    }
    for (size_t k = 0; k < res.size(); ++k) {
        cout << res[k] << endl;
    }
    return 0;
}

void minimo_costo(int cant_casas) {
    int r = 0;
    while (r < cant_casas - 1 && noTodos0(datos)) {
        if (datos[r] > 0) {
            buscarVendedor(r, r + 1);
        } else {
            buscarComprador(r, r + 1);
        }
        r = r + 1;
    }
}

void buscarComprador(int i, int j) {
    if (j < datos.size()) {
        if (datos[j] > 0) {
            if (abs(datos[i]) < datos[j]) {
                int x = (j - i) * abs(datos[i]);
                result += x;
                datos[j] = datos[i] + datos[j];
                datos[i] = 0;
            } else {
                if (abs(datos[i]) > datos[j]) {
                    int x = (j - i) * datos[j];
                    result += x;
                    datos[i] = datos[j] + datos[i];
                    datos[j] = 0;
                    buscarComprador(i, j + 1);
                } else {
                    if (abs(datos[i]) == datos[j]) {
                        int x = (j - i) * abs(datos[i]);
                        result += x;
                        datos[i] = 0;
                        datos[j] = 0;
                    }
                }
            }
        } else {
            buscarComprador(i, j + 1);
        }
    }
}

void buscarVendedor(int i, int j) {
    if (j < datos.size()) {
        if (datos[j] < 0) {
            if (abs(datos[j]) < datos[i]) {
                int x = (j - i) * abs(datos[j]);
                result += x;
                datos[i] = datos[i] + datos[j];
                datos[j] = 0;
                buscarVendedor(i, j + 1);
            } else {
                if (abs(datos[j]) > datos[i]) {
                    int x = (j - i) * datos[i];
                    result += x;
                    datos[j] = datos[j] + datos[i];
                    datos[i] = 0;
                } else {
                    if (abs(datos[j]) == datos[i]) {
                        int x = (j - i) * datos[i];
                        result += x;
                        datos[i] = 0;
                        datos[j] = 0;
                    }
                }
            }
        } else {
            buscarVendedor(i, j + 1);
        }
    }
}

bool noTodos0(const vector<int>& datos) {
    for (int i : datos) {
        if (i != 0) {
            return true;
        }
    }
    return false;
}
