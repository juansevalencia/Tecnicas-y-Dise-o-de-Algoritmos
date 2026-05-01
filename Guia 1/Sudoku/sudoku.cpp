#include <iostream>
#include <vector>

using namespace std;

struct tripla{
    int i;
    int j; 
    int primer_valor_q_tomo; //lo uso para verificar si el primer valor que tomo es el 2 estamos volviendo a ejecutar
};

vector<vector<vector<int>>> res;
tripla verificador_ciclo_inf;


bool cumpleSudoku(vector<vector<int>> grid, int row ,int col){
    //verifica si hay alguno igual
    //idea: recorre el cuadrante en que esta desde le principio y verifica si es igual
    int num = grid[row][col]; 
    // Check if we find the same num 
    // in the similar row , we
    // return false
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num)
            return false;
 
    // Check if we find the same num in 
    // the similar column , we
    // return false
    for (int x = 0; x <= 8; x++)
        if (grid[x][col] == num)
            return false;
 
    // Check if we find the same num in 
    // the particular 3*3 matrix,
    // we return false
    int startRow = row - row % 3, 
            startCol = col - col % 3;
   
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + 
                            startCol] == num)
                return false;
 
    return true;
}

void sudoku(int i, int j , int k , vector<vector<int>> T){
    if(verificador_ciclo_inf.i == i && verificador_ciclo_inf.j == j && verificador_ciclo_inf.primer_valor_q_tomo == k){
        //ya di toda la vuelta y no encontre otro
         //no va
    }else{
        if (T[i][j] != 0){
            if(j == 8){
                res.push_back(sudoku(i + 1 , 0 , k , T));
            } //si no es borde devolve sudoku de la prox columna en la misma fila.
            res.push_back(sudoku(i , j + 1 , k , T));
        }else{        
            if(i == 9){ //ya recorri todas las lineas
                res.push_back(T);
            }else{    
                if (j == 7){
                    vector<vector<int>> T_copy = T;
                    T_copy[i][j] = k;
                    if(cumpleSudoku(T_copy, i , j)){
                        sudoku(i + 1 , 0 , (k + 1 , T_copy); //lo agrego
                        sudoku(i, j , k + 1 , T);  //no lo agrego
                    }else{
                        //no lo puedo agregar xq no cumple sudoku agregarlo
                        if(verificador_ciclo_inf.i != i && verificador_ciclo_inf.j != j){
                            verificadior_ciclo_inf = {i , j , k};
                        }
                        sudoku(i ,j , k + 1 , T);
                    }
                }else{
                    vector<vector<int>> T_copy = T;
                    T_copy[i][j] = k;
                    if(cumpleSudoku(T_copy,i,j)){
                        sudoku(i , j + 1, k + 1 , T_copy); //lo agrego
                        sudoku(i , j , k + 1 , T);  //no lo agrego
                    }else{
                        //no lo puedo agregar xq no cumple sudoku agregarlo
                        if(verificador_ciclo_inf.i != i && verificador_ciclo_inf.j != j){
                            verificadior_ciclo_inf = {i , j , k};
                        }
                        sudoku(i  ,j , k + 1 , T);
                    }
                }
            }    
        }        
    }    if(verificador_ciclo_inf.i == i && verificador_ciclo_inf.j == j && verificador_ciclo_inf.primer_valor_q_tomo == k){
        //ya di toda la vuelta y no encontre otro
         //no va
    }else{
        if (T[i][j] != 0){
            if(j == 8){
                res.push_back(sudoku(i + 1 , 0 , k , T));
            } //si no es borde devolve sudoku de la prox columna en la misma fila.
            res.push_back(sudoku(i , j + 1 , k , T));
        }else{        
            if(i == 9){ //ya recorri todas las lineas
                res.push_back(T);
            }else{    
                if (j == 7){
                    vector<vector<int>> T_copy = T;
                    T_copy[i][j] = k;
                    if(cumpleSudoku(T_copy, i , j)){
                        sudoku(i + 1 , 0 , k + 1 , T_copy); //lo agrego
                        sudoku(i, j , k + 1 , T);  //no lo agrego
                    }else{
                        //no lo puedo agregar xq no cumple sudoku agregarlo
                        if(verificador_ciclo_inf.i != i && verificador_ciclo_inf.j != j){
                            verificadior_ciclo_inf = {i , j , k};
                        }
                        sudoku(i ,j , k + 1 , T);
                    }
                }else{
                    vector<vector<int>> T_copy = T;
                    T_copy[i][j] = k;
                    if(cumpleSudoku(T_copy,i,j)){
                        sudoku(i , j + 1, k + 1 , T_copy); //lo agrego
                        sudoku(i , j , k + 1 , T);  //no lo agrego
                    }else{
                        //no lo puedo agregar xq no cumple sudoku agregarlo
                        if(verificador_ciclo_inf.i != i && verificador_ciclo_inf.j != j){
                            verificadior_ciclo_inf = {i , j , k};
                        }
                        sudoku(i  ,j , k + 1 , T);
                    }
                }
            }    
        }        
    }
}

vector<vector<vector<int>>> init(vector<vector<int>> T){
    tripla verificador_ciclo_inf = {-1, -1 , -1};
    sudoku(0 ,0 ,1, T);
    return res;
}
int main(){
    vector<vector<int>> T = {{5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    vector<vector<vector<int>>> res = init(T);
    return 0;
}

//Me falta implementar que k rote, aplicaria un if si es igual a 10 que sea igual a 1