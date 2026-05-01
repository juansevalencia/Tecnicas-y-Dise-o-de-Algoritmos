#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

vector<int> puentes(vector<tuple<int ,int>> edges[]){
    vector<tuple<int, int>> res;
    int time = 0;

}

bool pertenece(tuple<int,int> elemento, const std::vector<tuple<int,int>>& vector) {
    for (tuple<int,int> i : vector) {
        if (i == elemento) {
            return true;
        }
    }
    return false;
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
            
            vector<int> ady[n+1];
            for (int cl = 0; cl < peso_wi.size(); cl++) {
                int acl = get<0>(peso_wi[cl]);
                int bcl = get<1>(peso_wi[cl]);

                int repacl = find(acl, link);
                int repbcl = find(bcl, link);

                if (repacl == repbcl) {
                    clasificacion[i - cl] = 0;
                    ya_clasifique_como_loop[i - cl] = true;
                } else {
                    ady[repacl].push_back(repbcl);
                    ady[repbcl].push_back(repacl);
                }
            }

            //dfs con lista de aristas
            vector<tuple<int,int>> puentes = puentes(ady);

            for(int iterator = 0 ; iterator < peso_wi.size() ; iterator ++ ){
                if(!ya_clasifique_como_loop[i - iterator]){
                    if(pertenece( {get<0>(peso_wi[iterator]), get<1>(peso_wi[iterator])}  , puentes)){ //pertenece a puentes
                        clasificacion[i - iterator] = 2; //any
                    }else{
                        clasificacion[i - iterator] = 1;
                    }
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
