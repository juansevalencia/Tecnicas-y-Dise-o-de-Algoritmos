#include<bits/stdc++.h>
using namespace std;
#define INF 9999⁹ 

int P, N;
vector<int> pesos;

int main(){
    cin >> P >> N;
    pesos.resize(N);
    for(int k = 0; k < N ; k++){
        cin >> pesos[k];
    }
}

int CDbottomUp(i, k){
    if(k < 0){
        return -INF; 
    }else{
        if(SumaRestante(i) <= k){
            return SumaRestante(i);
        }
    }
    return max(CDbottomUp(i + 1, k - pesos[i]) + pesos[i], CDbottomUp(i + 1, k ));
}

int SumaRestante(i){
    int res = 0;
    for(int k = i ; k < N , k++){
        res += pesos[k];
    }
    return res;
}
