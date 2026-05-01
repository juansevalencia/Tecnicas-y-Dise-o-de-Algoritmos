#include <iostream>
using namespace std;

vector<vector<int>> potSum(vector<vector<int>> A , i){
    if(i == 1){
        return A
    }else{
        vector<vector<int>> ant = potSum(A, i / 2 );
        vector<vector<int>> res = ant + mul_matriz(ant,A) ;
    }
}