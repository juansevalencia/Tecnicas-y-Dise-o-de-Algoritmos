#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

class Graph {
public:
    vector<unordered_set<int>> adjacency_list; // Cada nodo se identifica con un número

    int num_vertices;

    Graph(int vertices) : num_vertices(vertices) {
        adjacency_list.resize(num_vertices);
    }

    void add_edge(int v, int w) {
        adjacency_list[v].insert(w);
        adjacency_list[w].insert(v);
    }
};

vector<int> BFS_parity(Graph G, int start_vertex, vector<int> visited) {
    vector<int> parity(G.num_vertices, 0);
    parity[start_vertex] = 0;
    visited[start_vertex] = 1;

    queue<int> queue;
    queue.emplace(start_vertex);

    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();

        for (int neighbor : G.adjacency_list[v]) {
            if (visited[neighbor] == 0) { // Si no fue visitado
                parity[neighbor] = (parity[v] + 1) % 2;
                visited[neighbor] = 1;
                queue.emplace(neighbor);
            }
        }
    }
    return parity;
}

int main() {
    int num_vertices;
    cin >> num_vertices;

    Graph g(num_vertices);

    string line;
    long long int num_edges = num_vertices - 1; // Usar long long int para grandes números
    long long int r = 0;

    while (r < num_edges) {
        int u, v;
        cin >> u >> v; // Extrae los dos enteros de la línea
        g.add_edge(u - 1, v - 1); // Ajusta para índices cero
        r++;
    }

    vector<int> visited(num_vertices, 0);
    vector<int> parity = BFS_parity(g, 0, visited);
    long long int count_evens = 0;
    long long int count_odds = 0;

    for (int i = 0; i < num_vertices; i++) {
        // Cuenta cantidad de nodos pares e impares
        if (parity[i] == 0) {
            count_evens++;
        } else {
            count_odds++;
        }
    }

    long long int result = count_evens * count_odds - num_edges;
    cout << result;

    return 0;
}
