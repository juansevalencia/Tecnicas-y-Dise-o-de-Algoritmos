#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;
// 5 
//5 2 3 4 5
//0 1 2 2 1
class Graph {
public:
    vector<unordered_set<int>> adjacency_list; // Cada nodo se identifica con un número
    int num_vertices;

    Graph(int vertices) : num_vertices(vertices) {
        adjacency_list.resize(num_vertices + 1); // Aumentar el tamaño para incluir el índice 1
    }

    void add_edge(int v, int w) {
        adjacency_list[v].insert(w);
        adjacency_list[w].insert(v);
    }

    void add_atajo(int v , int w ){
        adjacency_list[v].insert(w);
    }
};

vector<int> BFS(Graph G , int cant_aulas){
    vector<int> distancias(cant_aulas + 1, -1); // Ajustar tamaño del vector
    queue<int> cola;
    cola.push(1); // Comenzar desde el nodo 1
    distancias[1] = 0;

    while(!cola.empty()){
        int v = cola.front();
        cola.pop();
        for(int neighbor : G.adjacency_list[v]){
            if(distancias[neighbor] == -1 ){
                distancias[neighbor] = distancias[v] + 1;
                cola.emplace(neighbor);
            }
        }
    }
    return distancias;
}   

int main(){
    int cant_aulas;
    cin >> cant_aulas;
    Graph g = Graph(cant_aulas);
    int atajo;
    for (int i = 1; i < cant_aulas; i++){ // Cambiar i a empezar desde 1
        cin >> atajo; 
        g.add_edge(i, i + 1);
        
        g.add_atajo(i, atajo); // No restar 1 aquí

    }
    cin >> atajo;
    g.add_atajo(cant_aulas, atajo); // No restar 1 aquí
    vector<int> distancias = BFS(g, cant_aulas);

    for(int r = 1; r <= cant_aulas; r++){ // Imprimir desde 1 hasta cant_aulas
        cout << distancias[r] << " ";
    }
    return 0;
}
