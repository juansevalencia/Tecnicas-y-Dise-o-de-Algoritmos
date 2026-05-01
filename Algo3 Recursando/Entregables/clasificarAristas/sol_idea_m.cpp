#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

void dfs(int u, vector<int>& discovery, vector<int>& low, vector<int>& parent,
          int& time, vector<pair<int, int>>& bridges, set<pair<int, int>>& visited_edges, vector<int> adj[]) {
    discovery[u] = low[u] = time++;
    
    for (int v : adj[u]) {
        pair<int, int> edge = make_pair(min(u, v), max(u, v));

        if (discovery[v] == -1) {
            parent[v] = u;
            dfs(v, discovery, low, parent, time, bridges, visited_edges, adj);

            low[u] = min(low[u], low[v]);

            if (low[v] > discovery[u]) {
                bridges.push_back(edge);
            }
        } else if (v != parent[u] && visited_edges.find(edge) == visited_edges.end()) {
            low[u] = min(low[u], discovery[v]);
            visited_edges.insert(edge);
        }
    }
}

vector<pair<int, int>> findBridges(int V, vector<int> adj[]) {
    vector<int> discovery(V, -1);
    vector<int> low(V, -1);
    vector<int> parent(V, -1);
    vector<pair<int, int>> bridges;
    set<pair<int, int>> visited_edges;
    int time = 0;

    for (int i = 0; i < V; i++) {
        if (discovery[i] == -1) {
            dfs(i, discovery, low, parent, time, bridges, visited_edges, adj);
        }
    }

    return bridges;
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

    for (int i = 1; i <= n; i++) {
        link[i] = i;
    }

    vector<tuple<int, int, int>> T;
    vector<int> clasificacion(edges.size(), 0);
    vector<bool> ya_clasifique_como_loop(edges.size(), false);

    for (int i = 0; i < edges.size(); i++) {
        int a = get<0>(edges[i]);
        int b = get<1>(edges[i]);
        int w = get<2>(edges[i]);

        vector<tuple<int , int, int>> peso_wi;
        peso_wi.push_back(edges[i]);

        while (i < edges.size() - 1 && w == get<2>(edges[i + 1])) {
            peso_wi.push_back(edges[i + 1]);
            i++;
        }

        if (peso_wi.size() > 1) {
            vector<int> Gp_ady[n + 1]; 
            for (int cl = 0; cl < peso_wi.size(); cl++) {
                int acl = get<0>(peso_wi[cl]);
                int bcl = get<1>(peso_wi[cl]);

                int repacl = find(acl, link);
                int repbcl = find(bcl, link);

                if (repacl == repbcl) {
                    clasificacion[i] = 0;
                    ya_clasifique_como_loop[i - cl] = true;
                } else {
                    Gp_ady[repacl].push_back(repbcl);
                    Gp_ady[repbcl].push_back(repacl);
                }
            }

            vector<pair<int,int>> bridges = findBridges(n, Gp_ady);

            for (int cl_b = 0; cl_b < peso_wi.size(); cl_b++) {
                if (!ya_clasifique_como_loop[i - cl_b]) {
                    int a_clb = get<0>(peso_wi[cl_b]);
                    int b_clb = get<1>(peso_wi[cl_b]);

                    int repa_clb = find(a_clb, link);
                    int repb_clb = find(b_clb, link);

                    bool es_bridge = false;
                    for (auto elem : bridges) {
                        if (elem == pair<int, int>(min(repa_clb, repb_clb), max(repa_clb, repb_clb))) {
                            es_bridge = true;
                            break;
                        }
                    }

                    clasificacion[i - cl_b] = es_bridge ? 2 : 1; // es_bridge ? "any" : "at least one";
                }
            }

        } else {
            if (!same(a, b, link)) {
                union_(a, b, link, size);
                T.push_back(edges[i]);
                clasificacion[i] = 2;

                if (T.size() == n - 1) break; // Stop if we have enough edges
            } else {
                clasificacion[i] = 0; // Conecta uno de una misma comp conexa
            }
        }
    }

    for (int i2 = 0; i2 < clasificacion.size(); i2++) {
        clasificacion_dic[edges[i2]] = (clasificacion[i2] == 0) ? "none" : 
                                         (clasificacion[i2] == 1) ? "at least one" : "any";
    }
}

int main() {
    vector<tuple<int, int, int>> edges;

    int n, m;
    cin >> n >> m;

    while (m-- > 0) {
        int a, b, w;
        cin >> a >> b >> w;
        edges.push_back({a, b, w});
    }

    map<tuple<int, int, int>, string> clasificacion_dic;
    Kruskal2(edges, clasificacion_dic, n);

    for (const auto& arista : edges) {
        cout << clasificacion_dic[arista] << endl;
    }

    return 0;
}
