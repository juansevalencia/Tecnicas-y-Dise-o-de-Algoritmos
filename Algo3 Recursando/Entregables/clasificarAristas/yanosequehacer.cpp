#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int INF = 1e9;

vector<int> raices;
vector<int> estado, memo, padre;
vector<vector<int>> tree_edges;
vector<int> back_edges_con_extremo_inferior_en, back_edges_con_extremo_superior_en;
unordered_map<tuple<int, int, int>, string> clasificacion_dic;

bool no_existe_igual(int repu, int repv) {
    int cant_ap = 0;
    for (int elem : tree_edges[repv]) {
        if (cant_ap >= 2) return false;
        if (elem == repu) cant_ap++;
    }
    return cant_ap < 2;
}

void dfs(int v, int p = -1) {
    estado[v] = 1;
    for (int u : tree_edges[v]) {
        if (estado[u] == 0) {
            tree_edges[v].push_back(u);
            padre[u] = v;
            dfs(u, v);
        } else if (u != padre[v] && estado[u] == 1) {
            back_edges_con_extremo_superior_en[u]++;
            back_edges_con_extremo_inferior_en[v]++;
        }
    }
    estado[v] = 2;
}

int cubren(int v, int p) {
    if (memo[v] != -1) return memo[v];
    int res = 0;
    for (int hijo : tree_edges[v]) {
        if (hijo != p) res += cubren(hijo, v);
    }
    res -= back_edges_con_extremo_superior_en[v];
    res += back_edges_con_extremo_inferior_en[v];
    memo[v] = res;
    return res;
}

bool pertenece(tuple<int, int> elemento) {
    for (tuple<int, int> i : back_edges) {
        if (i == elemento) return true;
    }
    return false;
}

int find(int x, vector<int>& link) {
    if (x != link[x]) link[x] = find(link[x], link);
    return link[x];
}

bool same(int x, int y, vector<int>& link) {
    return find(x, link) == find(y, link);
}

void union_(int x, int y, vector<int>& link, vector<int>& size) {
    int rep_x = find(x, link);
    int rep_y = find(y, link);
    if (rep_x != rep_y) {
        if (size[rep_x] < size[rep_y]) swap(rep_x, rep_y);
        link[rep_y] = rep_x;
        size[rep_x] += size[rep_y];
    }
}

void Kruskal2(vector<tuple<int, int, int>>& edges, int n) {
    sort(edges.begin(), edges.end(), [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
        return get<2>(a) < get<2>(b);
    });

    vector<int> link(n + 1);
    vector<int> size(n + 1, 1);
    vector<tuple<int, int, int>> T;
    vector<int> clasificacion(edges.size(), 0);

    // Inicializo las estructuras necesarias
    estado.assign(n + 1, 0);
    memo.assign(n + 1, -1);
    padre.assign(n + 1, -1);
    tree_edges.assign(n + 1, vector<int>());
    back_edges_con_extremo_inferior_en.assign(n + 1, 0);
    back_edges_con_extremo_superior_en.assign(n + 1, 0);

    for (int i = 1; i <= n; ++i) link[i] = i;

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
            for (int cl = 0; cl < peso_wi.size(); cl++) {
                int acl = get<0>(peso_wi[cl]);
                int bcl = get<1>(peso_wi[cl]);
                int repacl = find(acl, link);
                int repbcl = find(bcl, link);

                if (repacl == repbcl) {
                    clasificacion_dic[peso_wi[cl]] = "none";
                } else {
                    tree_edges[repacl].push_back(repbcl);
                    tree_edges[repbcl].push_back(repacl);
                }
            }

            for (int i = 1; i <= n; i++) {
                if (estado[i] == 0) {
                    dfs(i, -1);
                    raices.push_back(i);
                }
            }

            for (int iterator_puentes = 0; iterator_puentes < peso_wi.size(); iterator_puentes++) {
                int v = get<1>(peso_wi[iterator_puentes]);
                int p = padre[v];
                int repv_chequear = find(v, link);
                int repu_chequear = find(get<0>(peso_wi[iterator_puentes]), link);

                int elem = repv_chequear;
                for (int tree_ady : tree_edges[repv_chequear]) {
                    if (tree_ady == repu_chequear) elem = repu_chequear;
                }

                if (cubren(elem, p) == 0 && no_existe_igual(repu_chequear, repv_chequear) && 
                    !pertenece({repu_chequear, repv_chequear}) && !pertenece({repv_chequear, repu_chequear})) {
                    clasificacion_dic[peso_wi[iterator_puentes]] = "any";
                } else {
                    clasificacion_dic[peso_wi[iterator_puentes]] = "at least one";
                }
            }

            for (tuple<int, int, int> elem : peso_wi) {
                int primer = get<0>(elem);
                int segundo = get<1>(elem);
                if (!same(primer, segundo, link)) {
                    union_(primer, segundo, link, size);
                    T.push_back(elem);
                    if (T.size() == n - 1) break;
                }
            }

            for (int i = 0; i <= n; ++i) {
                tree_edges[i].clear();
                back_edges_con_extremo_inferior_en[i] = 0;
                back_edges_con_extremo_superior_en[i] = 0;
            }
            back_edges.clear();
        }
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

    Kruskal2(edges, n);

    for (const auto& arista : edges) {
        if (clasificacion_dic[arista].empty()) {
            clasificacion_dic[arista] = "none";
        }
    }

    for (const auto& arista : edges) {
        cout << clasificacion_dic[arista] << endl;
    }

    return 0;
}
