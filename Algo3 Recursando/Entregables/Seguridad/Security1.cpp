#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000000;

//CHEK LIST: complejidad , si cuando hay una multiarista la este seleccionando

vector<unordered_map<int,int>> veces_usadas;

int cam_min_rec(int dst, int n, vector<vector<int>> matriz, vector<int> padre, vector<int> dist){
    int res;
    if(dst == 0){
        return 1;
    }else{
        res = 0;
        for(int i = 0 ; i < n ; i++){
            if( dist[i] + matriz[dst][i] == dist[dst] ){ //que la distancia del adyacente mas el costo, sea igual a la distancia dela cgtual
                res+= cam_min_rec(i , n , matriz, padre, dist); //entonces tenemos un camino, me va a contar al padre dos veces?CHECL
                veces_usadas[dst][i] += 1; 
            }
        }
        return res;   
    }  
}

int minDistance(vector<int> dist , vector<bool> sptSet , int n){ 
    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++){
        if (sptSet[v] == false && dist[v] <= min){
            min = dist[v], min_index = v;
        }
    }

    return min_index;
}

int main(){
    
    //problema: Puedo llegar a tener mas de una arista entre dos esquinas, me afecta eso o es simplmeente poner la minima?
    //En una matriz de adyacencia se soluciona, piso valor

    //Puedo asumir que las longitudes de las calles son positivas, mas en especifico que nunca un loop va a mejorar mi longitud en un camino porque son positivas asi que decido ignorarlas


    int n, m;
    cin >> n >> m;

    vector<vector<int>> matriz_pesos(n,vector<int>(n,INF));

    int v, w ,c;
    for(int i = 0 ; i < m ; i++){
        cin >> v >> w >> c;
        
        matriz_pesos[v][w] = min(c, matriz_pesos[v][w]); 
        matriz_pesos[w][v] = min(c, matriz_pesos[w][v]);
    }

    if(n == 1){
        cout << matriz_pesos[0][0]; 
        return 0;
    }

    //imple GEEKS DOR GEEKS pero le agregue padre para recorrer
    vector<int> dist(n, INT_MAX);
    
    vector<int> padres(n);

    vector<bool> sptSet(n, false); //verdadero si el vertice  i esta incluido en un camino minimo

    dist[0] = 0;

    padres[0] = 0;

    for(int count = 0 ; count < n-1 ; count++){
        int u = minDistance(dist, sptSet, n );

        sptSet[u] = true;

        for(int v = 0 ; v < n ; v++){
            if( (!sptSet[v]) && (matriz_pesos[u][v]) && (dist[u] != INT_MAX) && (dist[u] + matriz_pesos[u][v] < dist[v]) ){ //actualiza valor de distancia de los adjacentrs al u
                dist[v] = dist[u] + matriz_pesos[u][v];
                padres[v] = u;
            }
        }
    }

    veces_usadas.resize(n);

    int cantidad_de_caminos_minimos_distintos = cam_min_rec(n-1, n, matriz_pesos, padres, dist);
    
    //recorro todas las aristas, buscando las que fueron usadas mas de dos veces en caminos minimos.
    int a_restar = 0;

    for(int i = 0; i < n ; i++){
        for(auto par : veces_usadas[i]){
                a_restar += (par.second - 1) * (matriz_pesos[i][par.first]);
        }
    }


    int respuesta = dist[n-1]*cantidad_de_caminos_minimos_distintos;

    respuesta -= a_restar;

    respuesta*= 2;

    //quiero recorrer el camino de v hacia el padre, que no necesariamente son n-1 nodos.
    cout << (respuesta) << endl;

    return 0;
}
