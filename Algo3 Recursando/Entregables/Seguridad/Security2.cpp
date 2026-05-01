#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = 1000000000;


vector<vector<pair<int,int>>> adj;
int n;

vector<int> djikstra(int v){
    vector<int> res(n, INF);
    res[v] = 0;

    vector<int> prev(n, -1);

    priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, greater<std::pair<int, int>>> pq;
    
    pq.push({0,v});

    while (!pq.empty()) {
        // Get the vertex with minimum distance
        int current_distance = pq.top().first;
        int current_vertex = pq.top().second;
        pq.pop();
        // If we've found a longer path, skip
        if (current_distance > res[current_vertex])
            continue;
        // Check all neighbors
        for (const auto& [neighbor, weight] : adj[current_vertex]) {
            // Calculate distance to neighbor through current vertex
            int distance = current_distance + weight;
            // If we found a shorter path, update
            if (distance < res[neighbor]) {
                res[neighbor] = distance;
                prev[neighbor] = current_vertex;
                pq.push({distance, neighbor});
            }
        }
    }

    return res;


}

int main(){

    int ret = 0;
    int m;
    cin >> n >> m;

    adj.resize(n);

    int v, w, c;
    for(int i = 0 ; i < m ; i++){
        cin >> v >> w >> c;
        //bidireccional, pusheo las dos
        adj[v].push_back({w,c});
        adj[w].push_back({v,c});    
    }

    vector<int> distanciasD0 = djikstra(0);

    vector<int> distanciasDn = djikstra(n-1);

    //recorre todas las aristas y fijate si pertenecen a algun camino minimo.

    //ya la recorri, para no contarla dos veces
    vector<bool> visitados(n , false);

    for(int i = 0; i < n ;i++){
        for(auto arista : adj[i] ){
            if(distanciasD0[i] + arista.second + distanciasDn[arista.first] == distanciasD0[n-1]){
                ret = ret + arista.second;
            }else{
                if(distanciasDn[i] + arista.second + distanciasD0[arista.first] == distanciasD0[n-1]){
                    ret = ret + arista.second;
                } //si no, no hagas nada
            }
        }
    }    
    
    cout << ret;

    return 0;
}