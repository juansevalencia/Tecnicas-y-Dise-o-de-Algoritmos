#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool f(int d , int vacasxasignar, vector<int>& B, int D, int ult, int cant_posiciones){
    if(vacasxasignar == 0){
        return true;
    }else{
        if((d == cant_posiciones)){
            return false;
        }else{
            int qc = B[d];
            int qcy = B[d]-B[ult];
            if(qcy >= D){
                return (f(d+1 , vacasxasignar - 1, B, D, d, cant_posiciones));
            }else{
                return (f(d +1 , vacasxasignar , B , D, d, cant_posiciones));
            }
        }
    }
}

int main(){
    int cant_casos;
    cin >> cant_casos;
    vector<int> resultfinal(cant_casos);

    int i = 0;
    while(cant_casos > i){
        int cant_posiciones;
        int cant_vacas;
        cin >> cant_posiciones >> cant_vacas;
        vector<int> B(cant_posiciones);

        for(int j = 0 ; j < cant_posiciones ;j++){
            cin >> B[j];
        }

        sort(B.begin(), B.end());

        int low = 1;
        int high = B[cant_posiciones - 1] - B[0];
        int best = 0;
        //binaria basada en chat
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (f(1, cant_vacas - 1, B, mid, 0, cant_posiciones)) {
                best = mid;  
                low = mid + 1;  
            } else {
                high = mid - 1;  
            }
        }
        resultfinal[i] = best;
        
        i++;
    }
    for(int t = 0 ; t < cant_casos ; t++){
        cout << resultfinal[t] << endl;
    }
    return 0;
}