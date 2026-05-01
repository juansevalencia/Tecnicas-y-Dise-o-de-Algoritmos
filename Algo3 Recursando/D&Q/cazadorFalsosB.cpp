#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> m;

bool f(int i0, int i1, int j0 , int j1){
    int res;
    if(i0 == i1){ //supongo que es pot de dos
        if(!m[i0][j1]){
            return 1;
        }
    } //filas , columnas
    int midrow = (i0 + i1)/2;
    int midcol = (j0 + j1)/2;
    if(!conjuncionSubMatriz(i0 , midrow , j0 , midcol)){ //primer cuadrante
        res+= f(0 , midrow , j0 , midcol);
    }if(!conjuncionSubMatriz(i0,midrow, midcol + 1 , j1 )){ //2do cuadrante
        res+= f( i0,midrow, midcol + 1 , j1);
    }if(!conjuncionSubMatriz(midrow + 1, i1 , j0 , midcol )){ //3er cuadrante
        res+= f(midrow + 1, i1 , j0 , midcol );
    }if(!conjuncionSubMatriz(midrow + 1 , i1, midcol +1 , j1)){
        res+= f(midrow + 1 , i1, midcol +1 , j1);
    }
    return res;
}