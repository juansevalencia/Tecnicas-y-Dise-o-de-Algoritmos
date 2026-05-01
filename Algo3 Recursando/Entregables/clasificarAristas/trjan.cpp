#include <bits/stdc++.h>

using namespace std;

class DisjointSet {
    vector<int> rank, parent;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for(int i = 0; i < n + 1; i++){
            parent[i] = i;
        }
    }
 
    int findSet(int node){
        if (node == parent[node]) return node;
        return parent[node] = findSet(parent[node]);
    }
 
    void unionByRank(int u, int v) {
        int uRepresentative = findSet(u);
        int vRepresentative = findSet(v);
 
        if (uRepresentative == vRepresentative) return;
 
        if (rank[uRepresentative] < rank[vRepresentative]) {
            parent[uRepresentative] = vRepresentative;
        } else if(rank[uRepresentative] > rank[vRepresentative]) {
            parent[vRepresentative] = uRepresentative;
        } else {
            parent[vRepresentative] = uRepresentative;
            rank[uRepresentative]++;
        }
    }
};

void dfs(int actual, int p, int profundidad, vector<vector<int>>& grafo, 
         vector<tuple<int,int,int,int>>& aristas, DisjointSet& set, 
         vector<int>& low, vector<int>& momento_visitado, vector<int>& descubrimiento, 
         vector<string>& clasificacion, int& tiempo) {
    
    momento_visitado[actual] = tiempo + 1;
    descubrimiento[actual] = profundidad;
    low[actual] = profundidad;

    for(int i = 0; i < grafo[actual].size(); i++) {
        if(grafo[actual][i] == p) continue;  // no considera la vuelta

        int id = grafo[actual][i];
        int a = set.findSet(get<0>(aristas[id]));
        int b = set.findSet(get<1>(aristas[id]));
        int vecino;
        
        if(a == actual) {
            vecino = b;
        } else {
            vecino = a;
        }

        if(momento_visitado[vecino] > tiempo) {
            low[actual] = min(low[actual], descubrimiento[vecino]);
        } else {
            dfs(vecino, grafo[actual][i], profundidad + 1, grafo, aristas, set, 
                low, momento_visitado, descubrimiento, clasificacion, tiempo);
            low[actual] = min(low[actual], low[vecino]);
        }

        if(low[vecino] > descubrimiento[actual]) {
            clasificacion[get<3>(aristas[grafo[actual][i]])] = "any";
        }
    }
}

void Kruskal2(vector<tuple<int, int, int,int>>& edges, int n, int m) {
    sort(edges.begin(), edges.end(), [](const tuple<int, int, int,int>& a, const tuple<int, int, int, int>& b) {
        return get<2>(a) < get<2>(b);
    });

    vector<string> clasificacion(m, "at least one");
    vector<vector<int>> grafo(n);  // Almacena índices de aristas en vez de nodos
    DisjointSet set(n);
    vector<int> low(n), descubrimiento(n), momento_visitado(n);
    int tiempo = 0;

    int e = 0;
    while(e < m) {
        int k = e;
        while(k < edges.size() && get<2>(edges[k]) == get<2>(edges[e])) k++;

        // Fase 1: Construir grafo temporal
        for(int j = e; j < k; j++) {
            int rep_a = set.findSet(get<0>(edges[j]));
            int rep_b = set.findSet(get<1>(edges[j]));

            if(rep_a != rep_b) {
                grafo[rep_a].push_back(j);  // Guardamos índice de la arista
                grafo[rep_b].push_back(j);
            } else {
                clasificacion[get<3>(edges[j])] = "none";
            }
        }

        // Fase 2: Ejecutar Tarjan
        for(int j = e; j < k; j++) {
            int rep_a = set.findSet(get<0>(edges[j]));
            int rep_b = set.findSet(get<1>(edges[j]));
            if(momento_visitado[rep_a] <= tiempo) {
                dfs(rep_a, -1, 0, grafo, edges, set, low, 
                    momento_visitado, descubrimiento, clasificacion, tiempo);
            }
            if(momento_visitado[rep_b] <= tiempo) {
                dfs(rep_b, -1, 0, grafo, edges, set, low, 
                    momento_visitado, descubrimiento, clasificacion, tiempo);
            }
        }

        // Fase 3: Unir componentes y limpiar
        for(int j = e; j < k; j++) {
            int rep_a = set.findSet(get<0>(edges[j]));
            int rep_b = set.findSet(get<1>(edges[j]));
            set.unionByRank(rep_a, rep_b);
            grafo[rep_a].clear();
            grafo[rep_b].clear();
        }

        e = k;
        tiempo++;
    }

    for(auto& elem : clasificacion) {
        cout << elem << endl;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int,int>> edges;
    
    for(int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--; b--;  // Ajuste para índices 0-based
        edges.push_back({a, b, w, i});
    }

    Kruskal2(edges, n, m);
    return 0;
}