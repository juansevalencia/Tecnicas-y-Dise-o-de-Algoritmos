#include <bits/stdc++.h>
using namespace std;

int INF = 9999;

tuple<int, int> minEncontrado;
tuple<int, int> res;
int n;
vector<int> B;
vector<vector<int>> M;

bool menor(tuple<int, int> res1 , tuple<int, int> minEncontrado){
    if(get<0>(res1) < get<0>(minEncontrado) || (get<0>(res1) == get<0>(minEncontrado) && get<1>(res1) < get<1>(minEncontrado))){
        return true;
    }else{
        return false;
    }
}

void cc(int i , int j ){
    if(M[i][j] != -1){
        ; //esto quiere decir que de alguna manera ya se calculo
    }else{
        if(j <= 0){
            if(menor(res, minEncontrado)){
                minEncontrado = res;
            }
        }else{
            if(i != n){
                res = {get<0>(res) + B[i], get<1>(res) + 1};
                cc(i + 1, j - B[i]);
                res = {get<0>(res) - B[i], get<1>(res) - 1};
                cc(i + 1, j);
            }
        }
        M[i][j] = 1;
    }    
}   


int main(){
    int c;
    cin >> c;
    cout << "Tamaño de entrada";    
    cin >> n;
    B.resize(n);


    cout << "inserta los elementos";
    for (int i = 0; i < n ; i++){
        cin >> B[i];
    }

    vector<vector<int>> Ms(n, vector<int>(c+1 , -1));

    M= Ms;
    res = {0, 0};
    minEncontrado = {INF, INF};

    cc(0,c);

    tuple<int, int> rest = minEncontrado;

    cout << get<0>(rest) << "," << get<1>(rest) << endl;
    return 0;
}