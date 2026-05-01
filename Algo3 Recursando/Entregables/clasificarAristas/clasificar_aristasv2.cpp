#include <iostream>
#include <vector>
#include <tuple>
#include <bitset>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

int find(int x, vector<int>& link) {
    if (x != link[x]) {
        link[x] = find(link[x], link); // Path compression
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

void Kruskal2(vector<tuple<int, int, int>>& edges, map<tuple<int,int,int> , string>& clasificacion_dic ,int n) {
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

    //como detecto si al menos dos tienen el mismo tamaño, mete todas las de un mismo tamaño en un vector
    vector<int> Gprima_adj[n+1];
    
    for (int i = 0; i < edges.size(); i++ ) { //OJO INDEXO EN 0 EN EDGES
        int a = get<0>(edges[i]);
        int b = get<1>(edges[i]);
        int w = get<2>(edges[i]);

        vector<tuple<int , int, int>> peso_wi;
        peso_wi.push_back(edges[i]);

    
        while( i < edges.size() - 1 && w == get<2>(edges[i+1])){
            if(peso_wi.size() == 1){
                int repa = find(a, link);
                int repb = find(b, link);

                if( repb == repa ){ //no lo metas en G' 
                    clasificacion[i] = 0;
                    ya_clasifique_como_loop[i] = true;
                }else{

                    Gprima_adj[repa].push_back(repb);
                    Gprima_adj[repb].push_back(repa);
                }
            }

            peso_wi.push_back(edges[i+1]);
            //pushea las aristas de las comp conexas

            int r = get<0>(edges[i+1]);
            int s = get<1>(edges[i+1]);

            int rep_r = find(r, link);
            int rep_s = find(s, link);
            
            if(rep_r == rep_s){
                clasificacion[i+1] = 0;
                ya_clasifique_como_loop[i] = true;
            }else{
                Gprima_adj[rep_r].push_back(rep_s);
                Gprima_adj[rep_s].push_back(rep_r);
            }

            i++;
        }

        if(peso_wi.size() > 1){
            //recorre las aristas en G' y verifica si las vertices tienen grado igual a 1 o mayor.
            vector<tuple<int,int>> representantes_viejos;
            
            //recorro los representantes antrs porque con el union se van a ir modificando..
            //y necesito eliminarlos de g'
            for(int i8 = 0; i8 < peso_wi.size();i8++){
                int a8 = get<0>(peso_wi[i8]);
                int b8 = get<1>(peso_wi[i8]);

                int repa8 = find(a8, link);
                int repb8 = find(b8, link);

                representantes_viejos.push_back({repa8, repb8});
            }


            bool ya_coloque_un_at_least = false;
            for(int i9 = 0; i9 < peso_wi.size(); i9++){
                if(!ya_clasifique_como_loop[i - i9]){
                    int a9 = get<0>(peso_wi[i9]);
                    int b9 = get<1>(peso_wi[i9]);

                    int repa = find(a9, link);
                    int repb = find(b9, link);

                    if( repa == repb ){

                        clasificacion[i- i9] = 1;  //es at least one a diferencia con la de abajo es que ya la uni. Porque a las que sean iguales ya las pushee antes.
                    }else{
                        if(Gprima_adj[repa].size() == 1 || Gprima_adj[repb].size() == 1){
                            //conecta hacia un puente
                            clasificacion[i - i9] = 2; //any

                            union_(a9,b9,link, size);
                            T.push_back(peso_wi[i9]);

                        }else{
                            //at least one, es la primera at least one de su ciclo
                            clasificacion[i - i9] = 1;

                            union_(a9, b9, link, size);

                            T.push_back(peso_wi[i9]);

                        }
                    } //tendria que sacar cada arista de G' 
                }
            }
            for(auto elem : representantes_viejos){    
                int repa_sacar = get<0>(elem);
                int repb_sacar = get<1>(elem);
                
                Gprima_adj[repa_sacar].erase(Gprima_adj[repa_sacar].begin());
                Gprima_adj[repb_sacar].erase(Gprima_adj[repb_sacar].begin());
            }
            //tendria que verificar si hubo aristas con clasificacion at least one. Meter una de ellas por cada cicl
        }else{
            if (!same(a, b, link)) { //es any
                union_(a, b, link, size);
                T.push_back(edges[i]);
                clasificacion[i] = 2;

                if (T.size() == n - 1) break; // Stop if we have enough edges
            }else{//el else aca seria que es none porque conecta uno de una misma comp conexa osea un ciclo
                clasificacion[i] = 0;
            }
        }
    }

    for(int i2 = 0; i2 < clasificacion.size() ; i2++){
        clasificacion_dic[edges[i2]] = (clasificacion[i2] == 0) ? "none" : 
                                 (clasificacion[i2] == 1) ? "at least one" : "any";
    }
}


int main(){

    vector<tuple<int, int, int>> edges;

    vector<bool> bitmap(1000001, 0); //entrada 10^6 peso max

    bool todos_distinto_peso = true;

    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges2;

    map<tuple<int,int,int>, string> clasificacion_dic;

    int cpy_m = m;
    while(cpy_m-- > 0){
        int a ,b, w;
        cin >> a >> b >> w;
        
        edges.push_back({a, b, w});
        edges2.push_back({a,b,w});
    }



    Kruskal2(edges,clasificacion_dic, n);
   

    for(auto arista : edges2){
        cout << clasificacion_dic[arista] << endl;
    }
    return 0;
}