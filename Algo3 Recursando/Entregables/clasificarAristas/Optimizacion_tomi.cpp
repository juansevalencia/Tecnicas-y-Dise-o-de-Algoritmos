#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;

unordered_map<int, unordered_map<int, int>> cant_aristas;
unordered_map<int, unordered_map<int, bool>> ady; //aca podria optimizar de alguna manera haciendo otra unordered map en vez de vector
int NO_LO_VI = 0, EMPECE_A_VER = 1, TERMINE_DE_VER = 2;
unordered_map<int,int> estado; 
unordered_map<int,int> memo;
unordered_map<int,int> padre;
unordered_map<int, vector<int>> tree_edges;
unordered_map<int, int> back_edges_con_extremo_inferior_en; //hago unordered map asi no tengo que crear de tamaño n, porque mi G'puede tener representnates
unordered_map<int,int> back_edges_con_extremo_superior_en; 
unordered_map<int,unordered_map<int,bool>> back_edges; 


void dfs(int v, int p = -1) {
    estado[v] = 1;
    for (auto& par : ady[v]) {
        int u = par.first;
        if (estado[u] == 0) {
            tree_edges[v].push_back(u);
            padre[u]=v;
            dfs(u, v);
        }
        else if (u != padre[v]) {
            if ( estado[u] == 1 ) {
                back_edges_con_extremo_superior_en[u]++;
                back_edges_con_extremo_inferior_en[v]++;
                back_edges[v][u] = true;
            }
        }
    }
    estado[v] = 2;

}

int cubren(int v, int p) {
    if (memo[v] != -1) return memo[v];
    int res = 0;
    for (int hijo : tree_edges[v]) {
        if (hijo != p) {
            res += cubren(hijo, v);
        }
    }
    res -= back_edges_con_extremo_superior_en[v];
    res += back_edges_con_extremo_inferior_en[v];
    memo[v] = res;
    return res;
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
    }); //ordena tus aristas

    vector<int> link(n + 1);
    vector<int> size(n + 1, 1);

    for (int i = 1; i <= n; i++) {
        link[i] = i;
    } 
    //kruskal

    vector<tuple<int, int, int>> T; //como mucho tamaño n, no puedo optimizar esto
    vector<bool> ya_clasifique_como_loop(edges.size(), false); //O(m) ,al fin y al cabo voy a recorrer todas]?
 
    //inicializo variables globales

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

            map<int, int> representantes;

            for (int cl = 0; cl < peso_wi.size(); cl++) {
                int acl = get<0>(peso_wi[cl]);
                int bcl = get<1>(peso_wi[cl]);

                int repacl = find(acl, link);
                int repbcl = find(bcl, link);


                if (repacl == repbcl) {
                    clasificacion_dic[peso_wi[cl]] = "none";
                    ya_clasifique_como_loop[i - cl] = true;
                } else {
                    representantes[acl] = repacl;
                    representantes[bcl] = repbcl;
                    ady[repacl][repbcl] = true;
                    ady[repbcl][repacl] = true;
                    cant_aristas[repacl][repbcl] += 1;
                    cant_aristas[repbcl][repacl] += 1; //esta bien marcar lso dos?
                }
            }

            for(auto& par: ady){
                int vertice = par.first;
                memo[vertice] = -1;
                estado[vertice] = 0;
                padre[vertice] = -1;
                back_edges_con_extremo_inferior_en[vertice] = 0;
                back_edges_con_extremo_superior_en[vertice] = 0;
            }

            for(auto& iterator_dfs : ady ){ 
                if(estado[iterator_dfs.first] == 0 ){
                    dfs(iterator_dfs.first,-1);                   
                }
            }


            for(int iterator_puentes = 0; iterator_puentes < peso_wi.size() ; iterator_puentes++){
                if(!ya_clasifique_como_loop[i-iterator_puentes]){                                                                                 
                    
                    int v = get<1>(peso_wi[iterator_puentes]);
                    int p = padre[v]; 

                    int repv_chequear = representantes[v];
                    int repu_chequear = representantes[get<0>(peso_wi[iterator_puentes])];
                    
                     //hace que seleccione el nodo desde donde es apuntado por la arista

                    int elem = repv_chequear;
                    
                    for(auto tree_ady : tree_edges[repv_chequear]){
                        if(tree_ady == repu_chequear){
                            //entonces al el nodo u es apuntado por la tree edge
                            elem = repu_chequear;
                            break;
                        }
                    }
                    //para que sea any tiene que ser puente, no tiene que ser multiarista, y no tiene que ser una back edge
                    if(cubren(elem ,p ) == 0 && cant_aristas[repu_chequear][repv_chequear] == 1  && !back_edges[repu_chequear][repv_chequear] && !back_edges[repu_chequear][repv_chequear]){ //chequeo que no sea multiarista
                        clasificacion_dic[peso_wi[iterator_puentes]] = "any"; //any
                    }else{
                        clasificacion_dic[peso_wi[iterator_puentes]] = "at least one";
                    }
                }    
            }

            //kruskal

            for(tuple<int,int,int> elem : peso_wi){
                int primer = get<0>(elem);
                int segundo = get<1>(elem);     
                if (!same(primer, segundo, link)) {
                    union_(primer, segundo, link, size);
                    T.push_back(elem);
        
                    if (T.size() == n - 1) break; // Stop if we have enough edges
                }
            }


            ady.clear();

            tree_edges.clear();

            back_edges.clear();

            estado.clear();

            memo.clear();

            padre.clear();

            back_edges_con_extremo_inferior_en.clear();
            
            back_edges_con_extremo_superior_en.clear();

            back_edges.clear();

        } else {
            if (!same(a, b, link)) {
                union_(a, b, link, size);
                T.push_back(edges[i]);
                clasificacion_dic[edges[i]] = "any";

                if (T.size() == n - 1) break; // Stop if we have enough edges
            } else {
                clasificacion_dic[edges[i]] = "none"; // Conecta uno de una misma comp conexa
            }
        }
    }

}

int main() {
    vector<tuple<int, int, int>> edges;
    vector<tuple<int, int, int>> edges2;

    int n, m;
    cin >> n >> m;

    while (m-- > 0) {
        int a, b, w;
        cin >> a >> b >> w;
        edges.push_back({a, b, w});
        edges2.push_back({a, b, w}); 
    }


    map<tuple<int, int, int>, string> clasificacion_dic;
    Kruskal2(edges, clasificacion_dic, n);



    for (const auto& arista : edges2) {
        if(clasificacion_dic[arista].empty()){
            cout << "none" <<endl;
        }else{
            cout << clasificacion_dic[arista] << endl;
        }
    }

    return 0;
}
