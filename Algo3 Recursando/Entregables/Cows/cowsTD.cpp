#include <bits/stdc++.h>
using namespace std;
#include <iostream>
#include <algorithm>

// Función para construir un heap máximo a partir de un subárbol
void heapify(vector<int>& vec, int n, int i) {
    int largest = i; // Inicialmente, el mayor es la raíz
    int left = 2 * i + 1; // Índice del hijo izquierdo
    int right = 2 * i + 2; // Índice del hijo derecho

    // Verifica si el hijo izquierdo existe y es mayor que la raíz
    if (left < n && vec[left] > vec[largest]) {
        largest = left;
    }

    // Verifica si el hijo derecho existe y es mayor que la raíz
    if (right < n && vec[right] > vec[largest]) {
        largest = right;
    }

    // Si el mayor no es la raíz
    if (largest != i) {
        swap(vec[i], vec[largest]);

        // Aplica heapify al subárbol afectado
        heapify(vec, n, largest);
    }
}

// Función principal para ordenar un vector usando HeapSort
void heapSort(vector<int>& vec) {
    int n = vec.size();

    // Construye un heap máximo
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(vec, n, i);
    }

    // Extrae elementos uno a uno del heap
    for (int i = n - 1; i > 0; i--) {
        // Mueve la raíz del heap (el mayor elemento) al final del vector
        swap(vec[0], vec[i]);

        // Llama a heapify en el heap reducido
        heapify(vec, i, 0);
    }
}

int Posiciones;
int minimaDist;
int ultimo_elegido;
vector<vector<int>> M;


int mmd(int i , int restantes, vector<int> vector_posiciones){
    if(M[i][restantes] != -1){
        return M[i][restantes];
    }else{
        if(restantes == 0){
            return minimaDist;
        }else{
            int q = Posiciones;
            q = q - 1;
            if(((i == q) && (restantes>0))){
                M[i][restantes] = -11; //porque no guarda en mi matriz el valor este?
                return -11; //porque se saltea esta linea?
            }else{
                int b = mmd(i + 1 , restantes ,vector_posiciones);
                int atras = vector_posiciones[i] - ultimo_elegido;
                int adelante = vector_posiciones[Posiciones - 1] - vector_posiciones[i];
                int menorDist = min({atras, menorDist , adelante});
                if(minimaDist > atras || (minimaDist > adelante)){
                    ultimo_elegido = vector_posiciones[i];
                }
                minimaDist = menorDist;
                int a = mmd(i+ 1 , restantes - 1, vector_posiciones);
                //tengo que volver a setear ultimo_elegido?
                M[i][restantes] = max(a, b);
            }
        }
    }
    return M[i][restantes];
}

int main(){
    int cantidad_casos;
    cin >> cantidad_casos;
    vector<int> res(cantidad_casos, 0);
    while(cantidad_casos > 0){    
        int vacas_por_asignar;
        cin >> Posiciones >> vacas_por_asignar;
        vector<int> vector_posiciones(Posiciones);
        for(int i =0 ; i < Posiciones ; i++){
            cin >> vector_posiciones[i];
        }
        heapSort(vector_posiciones);
        vector<vector<int>> matriz(Posiciones ,vector<int>(vacas_por_asignar - 1, -1));
        M = matriz;
        minimaDist = vector_posiciones[Posiciones - 1] - vector_posiciones[0];
        ultimo_elegido = vector_posiciones[0];
        res[cantidad_casos - 1] = mmd(1, vacas_por_asignar - 2, vector_posiciones); //ACORDATE DE PRINTEARLO DADO VUELTA BOLU
        cantidad_casos --;
    }
    for(int i = cantidad_casos - 1; i >= 0 ;i--){
        cout << res[i] << endl;
    }
    return 0;
}
