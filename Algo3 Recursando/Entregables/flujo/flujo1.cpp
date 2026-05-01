#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>
using namespace std;

#define INF 1e9

//implmeentacion de F&F basada en geeks for geeks pero usando vector<int> y no arrays

vector<vector<int>> rGraph;

bool bfs(vector<vector<int>>& rGraph, int s, int t, vector<int>& parent)
{
    int V = rGraph.size();
    // Create a visited array and mark all vertices as not visited
    vector<bool> visited(V, false);

    // Create a queue, enqueue source vertex and mark source vertex as visited
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                // If we find a connection to the sink node,
                // then there is no point in BFS anymore
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    // We didn't reach sink in BFS starting from source, so return false
    return false;
}

// Returns the maximum flow from s to t in the given graph
int fordFulkerson(vector<vector<int>>& graph, int s, int t)
{
    int V = graph.size();
    // Create a residual graph and fill the residual graph
    // with given capacities in the original graph as
    // residual capacities in residual graph
    rGraph = graph;

    // This vector is filled by BFS and to store path
    vector<int> parent(V); //es el v nuevo, no el viejo

    int max_flow = 0; // There is no flow initially

    // Augment the flow while there is path from source to sink
    while (bfs(rGraph, s, t, parent)) {
        // Find minimum residual capacity of the edges along the path
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // Update residual capacities of the edges and reverse edges along the path
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    // Return the overall flow

    return max_flow;
}

// Driver program to test above functions
int main()
{
    int V, m;
    cin >> V >> m;

    // Create the graph as a 2D vector
    vector<vector<int>> graph(2*V + 2, vector<int>(2*V+2, 0));

//aulas se indexan en 1 asi que ponemos al nodo 0 como s y a t como 2n+1
//a los demas es +V

    int flujo_max = 0;

    // Input para ai
    for (int i = 1; i <= V; i++) {
        int ai;
        cin >>ai;
        graph[0][i] = ai;
        //hace falta bidireccional?

        flujo_max += ai;
    }
    int suma_bi = 0;

    for(int i = 1 ; i <= V; i++){
        int bi;
        cin >> bi;
        graph[V + i][2*V+1] = bi;
        graph[i][V + i] = INF; //agrrego la posibilidad de q se puedan mantener en la misma aula tambn
        suma_bi += bi;
    }

    //m lineas
    for(int i = 0 ; i < m ; i++){
        int p, q;
        cin >> p >> q;

        graph[p][V + q] = INF;
        graph[q][V + p] = INF;
    } 

    if( suma_bi == flujo_max && fordFulkerson(graph, 0, 2*V +1) == flujo_max){
        cout << "YES" << endl;
        for(int i = 1; i <= V ; i++){
            for(int j = 1; j <= V ;j++){
                cout << graph[i][V + j] - rGraph[i][V + j] <<" ";   
            }
            cout << endl;
        }
    }else{
        cout << "NO" << endl;
    }
    return 0;
}