#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>
#include <sstream>
#include <string>


using namespace std;


class Graph{
public:
    vector<unordered_set<int>> lista_de_ady; //cada nodo se identifica con numero, del nodo 0 a 1
    
    vector<unordered_set<int>> lista_de_no_ady;

    int cant_vertices;
    
    Graph(int vertices): cant_vertices(vertices){
        lista_de_ady.resize(cant_vertices);
        lista_de_no_ady.resize(cant_vertices);
        
        unordered_set<int> lista = {};
        for (int i = 0 ; i < cant_vertices ; i++){
            lista.insert(i);
        }

        for(int i = 0 ; i <cant_vertices ; i++){
            unordered_set<int> lista_cpy = lista;
            lista_cpy.erase(i); 
            lista_de_no_ady[i] =lista_cpy;
        }
    }

    void agregar_arista(int v , int w ){
        lista_de_ady[v].insert(w);
        lista_de_ady[w].insert(v);

        lista_de_no_ady[v].erase(w);
        lista_de_no_ady[w].erase(v);
    }
   
};


vector<int> BFS_paridad(Graph G, int v , vector<int> visitado){  
    
    vector<int> paridad_(G.cant_vertices , 0);

    paridad_[v] = 0;
    visitado[v] = 1;

    queue<int> queue;
    queue.emplace(v);
    
    int paridad = 1;
    while(!queue.empty()){

        int v = queue.front();
        queue.pop();

        for (int vecino : G.lista_de_ady[v]){
            if(visitado[vecino] == 0){ //si no fue visitado
                visitado[vecino] = 1;
                paridad_[vecino] = paridad;
                queue.emplace(vecino);
            }
        }
        paridad = (paridad + 1) % 2;

    }
    return paridad_;
}

int main(){
    //completa lista de adyacencia
    int cant_vert;
    cin >> cant_vert;

    Graph g(cant_vert);
    g.cant_vertices = cant_vert;

    string linea;
    int cant_aristas = cant_vert - 1;
    int r = 0;
    while (r < cant_aristas){
        int u, v;
        cin >> u >> v; // Extrae los dos enteros de la línea
        g.agregar_arista(u - 1, v - 1); // Ajusta para índices cero
        r++;
    }

    vector<int> visitado(cant_vert , 0);
    vector<int> paridad = BFS_paridad(g , 0 , visitado);
    
    int res = 0;
    for( int i = 0 ; i < cant_vert ;i++){
        for(int no_vecino : g.lista_de_no_ady[i]){
            if(paridad[no_vecino] != paridad[i]){
                g.lista_de_ady[i].insert(no_vecino);
                g.lista_de_ady[no_vecino].insert(i);
                g.lista_de_no_ady[no_vecino].erase(i);
                res++;
            }
        }       
    }
    cout << res;
    
    return 0;

}
