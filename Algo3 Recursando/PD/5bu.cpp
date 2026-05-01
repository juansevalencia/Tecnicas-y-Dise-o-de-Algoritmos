#include <bits/stdc++.h>
using namespace std;

bool ssbu(vector<int> c , int k){
    vector<bool> res(k + 1, false);
    res[0] = true;
    //por cada numero en la lista c verifico si sumo con algun otro numero de c o solo si suma de 1 a k verifico si hay algun numero que lo sum
    for(int i = 0 ; i < c.size() ; i++){
        for(int j = 0 ; j <= k; j++ ){
            res[i] = res[i] || ((j - c[i] >= 0) && res[j - c[i]]);
        }
    }
    return res[k];
}

int main() {
    vector<int> c; 
    int k, n;
    cout << "cantidad de elementos?";
    cin >> n;
    c.resize(n);

    cout << "inserta los elementos";
    for (int i = 0; i < n ; i++){
        cin >> c[i];
    }
    cin >> k;

    bool res1 = ssbu(c, k);
    if(res1){
        cout << "True" << endl;
    }else{
        cout << "False" << endl;
    }   
    return 0;
}
