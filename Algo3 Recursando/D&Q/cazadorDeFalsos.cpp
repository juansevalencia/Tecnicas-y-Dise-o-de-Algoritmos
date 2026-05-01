#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> m;

bool f(int i0, int i1, int j0 , int j1){
    if(i0 == i1){ //supongo que es pot de dos
        if(!m[i0][j1]){
            return true;
        }
    } //filas , columnas
    int midrow = (i0 + i1)/2;
    int midcol = (j0 + j1)/2;
    if(!conjuncionSubMatriz(i0 , midrow , j0 , midcol)){ //primer cuadrante
        return f(0 , midrow , j0 , midcol);
    }else if(!conjuncionSubMatriz(i0,midrow, midcol + 1 , j1 )){ //2do cuadrante
        return f( i0,midrow, midcol + 1 , j1);
    }else if(!conjuncionSubMatriz(midrow + 1, i1 , j0 , midcol )){ //3er cuadrante
        return f(midrow + 1, i1 , j0 , midcol ));
    }else{
        return f(midrow + 1 , i1, midcol +1 , j1);
    }
}