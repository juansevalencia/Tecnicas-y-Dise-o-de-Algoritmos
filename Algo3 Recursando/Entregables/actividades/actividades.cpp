#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

tuple<int,int> actividad_que_termina_antes(int k , vector<tuple<int,int>> act){
    int min1 = 9999999;
    int min0 = k;
    for (int i = 0; i < size(act) ; i++){
        int cpy = get<0>(act[i]);
        int cpy1 = get<1>(act[i]);
        if(cpy >= k && cpy1 < min1){
            min0 = cpy;
            min1 = cpy1;
        }
    }
    return make_pair(min0, min1);
}    

int main(){
    int cant_casos;
    cin >> cant_casos;
    vector<int> result(cant_casos);
    int cant2 = cant_casos;
    while(cant_casos > 0){
        int cant_actividades;
        cin >> cant_actividades;
        vector<tuple<int,int>> actividades(cant_actividades);
        int i = 0;
        while(cant_actividades > i){
            cin >> get<0>(actividades[i]) >> get<1>(actividades[i]);
            i++;
        }
        int res = 0;
        int k = -1;
        bool sigo = true;
        int old_primero = -1;
        while(sigo){
            tuple<int,int> val = actividad_que_termina_antes(k,actividades);
            int primero = get<0>(val);
            if((old_primero==primero || get<1>(val) == 9999999)){
                result[cant_casos - 1] = res;
                sigo = false;
            }else{
                old_primero = k;
                k = get<1>(val);
                res++;
            }
        }
        cant_casos --;
    }
    for (int j = cant2 ; j > 0 ; j--){
        cout << result[j-1] <<endl;
    }       
    return 0;
}
