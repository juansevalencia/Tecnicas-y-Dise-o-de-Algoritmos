#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

unordered_map<int, unordered_map<int, int>> cant_aristas;
unordered_map<int, unordered_map<int, bool>> ady;
unordered_map<int,int> discovery_time;
unordered_map<int,int> low;
int tiempo = 0;

void find_bridges(int u, int parent, unordered_map<int, vector<pair<int,bool>>>& bridges) {
    discovery_time[u] = low[u] = ++tiempo;
    
    for (auto& [v, _] : ady[u]) {
        if (v == parent) continue;
        
        if (discovery_time[v] == 0) {
            find_bridges(v, u, bridges);
            low[u] = min(low[u], low[v]);
            
            if (low[v] > discovery_time[u]) {
                // Es un puente si además no es una multiarista
                bridges[u].push_back({v, cant_aristas[u][v] == 1});
            }
        } else {
            low[u] = min(low[u], discovery_time[v]);
        }
    }
}

int find(int x, vector<int>& link) {
    if (x != link[x]) {
        link[x] = find(link[x], link);
    }
    return link[x];
}

bool same(int x, int y, vector<int>& link) {
    return find(x, link) == find(y, link);
}

void union_(int x, int y, vector<int>& link, vector<int>& size) {
    int rep_x = find(x, link);
    int rep_y = find(y, link);

    if (rep_x != rep_y) {
        if (size[rep_x] < size[rep_y]) {
            swap(rep_x, rep_y);
        }
        link[rep_y] = rep_x;
        size[rep_x] += size[rep_y];
    }
}

void Kruskal2(vector<tuple<int, int, int>>& edges, map<tuple<int,int,int>, string>& clasificacion_dic, int n) {
    sort(edges.begin(), edges.end(), [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
        return get<2>(a) < get<2>(b);
    });

    vector<int> link(n + 1);
    vector<int> size(n + 1, 1);
    for (int i = 1; i <= n; i++) link[i] = i;

    vector<tuple<int, int, int>> T;  // Árbol de expansión
    vector<bool> ya_clasifique_como_loop(edges.size(), false);

    // Aquí agrupamos las aristas con el mismo peso para que podamos procesarlas juntas
    for (int i = 0; i < edges.size(); i++) {
        int a = get<0>(edges[i]);
        int b = get<1>(edges[i]);
        int w = get<2>(edges[i]);

        vector<tuple<int, int, int>> peso_wi;
        peso_wi.push_back(edges[i]);

        // Agrupar aristas con el mismo peso
        while (i < edges.size() - 1 && w == get<2>(edges[i + 1])) {
            peso_wi.push_back(edges[i + 1]);
            i++;
        }

        // Si hay más de una arista con el mismo peso, clasificamos y procesamos juntas
        if (peso_wi.size() > 1) {
            tiempo = 0;
            discovery_time.clear();
            low.clear();
            
            unordered_map<int, vector<pair<int,bool>>> bridges;
            ady.clear();  // Limpiar la lista de adyacencia antes de procesar el nuevo grupo

            // Ejecutar Tarjan para el grupo de aristas con el mismo peso
            for (auto& [a, b, w] : peso_wi) {
                ady[a][b] = true;
                ady[b][a] = true;
                cant_aristas[a][b]++;
                cant_aristas[b][a]++;
            }

            // Ejecutar Tarjan en todos los nodos involucrados en las aristas del mismo peso
            for (auto& [v, _] : ady) {
                if (discovery_time[v] == 0) {
                    find_bridges(v, -1, bridges);
                }
            }

            // Clasificar las aristas dentro de peso_wi según si son puentes o no
            for (int iterator_puentes = 0; iterator_puentes < peso_wi.size(); iterator_puentes++) {
                int v = get<0>(peso_wi[iterator_puentes]);
                int u = get<1>(peso_wi[iterator_puentes]);
                
                bool is_bridge = false;
                // Verificar si la arista (v, u) es un puente
                for (const auto& [bridge_v, is_single] : bridges[v]) {
                    if (bridge_v == u && is_single) {
                        is_bridge = true;
                        break;
                    }
                }

                if (is_bridge) {
                    clasificacion_dic[peso_wi[iterator_puentes]] = "any";
                } else {
                    clasificacion_dic[peso_wi[iterator_puentes]] = "at least one";
                }
            }
        }

        // Procesar cada arista dentro de peso_wi
        for (tuple<int, int, int> elem : peso_wi) {
            int primer = get<0>(elem);
            int segundo = get<1>(elem);     
            if (!same(primer, segundo, link)) {
                union_(primer, segundo, link, size);
                T.push_back(elem);
                if (T.size() == n - 1) break;
            }
        }
    }
}

int main() {
    vector<tuple<int, int, int>> edges;
    vector<tuple<int, int, int>> edges2;

    int n, m;
    cin >> n >> m;

    // Leer las aristas
    while (m-- > 0) {
        int a, b, w;
        cin >> a >> b >> w;
        edges.push_back({a, b, w});
        edges2.push_back({a, b, w}); 
    }

    map<tuple<int, int, int>, string> clasificacion_dic;
    Kruskal2(edges, clasificacion_dic, n);

    // Imprimir los resultados
    for (const auto& arista : edges2) {
        if (clasificacion_dic[arista].empty()) {
            cout << "none" << endl;
        } else {
            cout << clasificacion_dic[arista] << endl;
        }
    }

    return 0;
}
