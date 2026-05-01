#include <bits/stdc++.h>
using namespace std;

int INF = 9999;

tuple<int, int> minEncontrado;
tuple<int, int> res;
int n;

bool menor(tuple<int, int> res1 , tuple<int, int> minEncontrado){
    if(get<0>(res) < get<0>(minEncontrado) || (get<0>(res1) == get<0>(minEncontrado) && get<1>(res1) < get<1>(minEncontrado))){
        return true;
    }else{
        return false;
    }
}

void cc(int i , int j , vector<int> B){
    if(j <= 0){
        if(menor(res, minEncontrado)){
            minEncontrado = res;
        }
    }else{
        if(i != n){
            res = {get<0>(res) + B[i], get<1>(res) + 1};
            cc(i + 1, j - B[i], B);
            res = {get<0>(res) - B[i], get<1>(res) - 1};
            cc(i + 1, j, B);
        }
    }
}


int main(){
    vector<int> B;
    int c;

    cin >> c;
    cout << "Tamaño de entrada";    
    cin >> n;
    B.resize(n);


    cout << "inserta los elementos";
    for (int i = 0; i < n ; i++){
        cin >> B[i];
    }

    res = {0, 0};
    minEncontrado = {INF, INF};

    cc(0,c,B);

    tuple<int, int> rest = minEncontrado;

    cout << get<0>(rest) << "," << get<1>(rest) << endl;
    return 0;


}