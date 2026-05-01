#include <heap>

int n;
int k;
vector<vector<int>> matriz;
vector<int> maximas_columnas;
vector<int> maximas_filas;
vector<int> maximos;

vector<int> buscarMaximo(){
    heap = [];
    i = 0;
    j = 0;
    while(i < n && j < n){
        heap.push(matriz[i][j] , <i,j>)
        i++;
        j++;
    }
    return heap;
}

int columnas_mayor(){
    //ordenan las columnas que mas sumen
}

int filas_mayor(){
    //ordena las filas que mas sumen
}

int ms(int i , vector<int> res){
    if(i == n || size(res) == k){
        return sumatoria(i , j, res);
    }
    return max(ms(i + 1 , res++ maximas_columnas.head()) , ms(i + 1, res ++maximas_filas.head()), ms(i + 1 , res ++ maximos) );
    //aca tengo el problema de que se me pueden cruzar caminos. Meter i iguales- Al fin y al cabo es lo mismo.s
}

struct nodo{
    int valor;
    <int;int> posicion;
}

int main(int n_, int k_){
    maximas_columnas = columnas_mayor();
    maximas_filas = filas_mayor();
    maximos = buscar_maximos();
    n = n_;
    k = k_;

}
