#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
    vector<int> rank, parent;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for(int i = 0; i < n + 1; i++){
            parent[i] = i;
        }
    }
 
    int findSet(int node){
        if (node == parent[node]) return node;
        return parent[node] = findSet(parent[node]);
    }
 
    void unionByRank(int u, int v) {
        int uRepresentative = findSet(u);
        int vRepresentative = findSet(v);
 
        if (uRepresentative == vRepresentative) return;
 
        if (rank[uRepresentative] < rank[vRepresentative]) {
            parent[uRepresentative] = vRepresentative;
        } else if(rank[uRepresentative] > rank[vRepresentative]) {
            parent[vRepresentative] = uRepresentative;
        } else {
            parent[vRepresentative] = uRepresentative;
            rank[uRepresentative]++;
        }
    }
};

void findBridges(int currentNode, int parentEdgeIdx, int depth,
                 vector<vector<int>>& adjList,
                 const vector<tuple<int,int,int,int>>& edges,
                 DisjointSet& ds,
                 vector<int>& earliest,
                 vector<int>& timeStamp,
                 vector<int>& discoveryDepth,
                 vector<string>& edgeType,
                 int& currentTime) {
    
    timeStamp[currentNode] = currentTime + 1;
    discoveryDepth[currentNode] = depth;
    earliest[currentNode] = depth;

    for(int edgeIdx : adjList[currentNode]) {
        if(edgeIdx == parentEdgeIdx) continue;

        int rootA = ds.findSet(get<0>(edges[edgeIdx]));
        int rootB = ds.findSet(get<1>(edges[edgeIdx]));
        int neighbor = (rootA == currentNode) ? rootB : rootA;

        if(timeStamp[neighbor] <= currentTime) {
            findBridges(neighbor, edgeIdx, depth + 1, adjList, edges, ds,
                       earliest, timeStamp, discoveryDepth, edgeType, currentTime);
            earliest[currentNode] = min(earliest[currentNode], earliest[neighbor]);
        } else {
            earliest[currentNode] = min(earliest[currentNode], discoveryDepth[neighbor]);
        }

        if(earliest[neighbor] > discoveryDepth[currentNode]) {
            edgeType[get<3>(edges[edgeIdx])] = "any";
        }
    }
}

void processEdgeGroups(vector<tuple<int,int,int,int>>& edges, int vertices, int edgeCount) {
    vector<string> edgeType(edgeCount, "at least one");
    vector<vector<int>> adjList(vertices); 
    DisjointSet ds(vertices);
    
    vector<int> earliest(vertices);
    vector<int> discoveryDepth(vertices);
    vector<int> timeStamp(vertices, 0);
    int currentTime = 0;
    
    sort(edges.begin(), edges.end(), 
         [](const auto& a, const auto& b) { return get<2>(a) < get<2>(b); });
    
    int currentEdge = 0;
    while(currentEdge < edgeCount) {
        int groupEnd = currentEdge;
        int currentWeight = get<2>(edges[currentEdge]);
        
        while(groupEnd < edgeCount && get<2>(edges[groupEnd]) == currentWeight) {
            groupEnd++;
        }
        
        // Construir grafo temporal
        for(int i = currentEdge; i < groupEnd; i++) {
            int rootA = ds.findSet(get<0>(edges[i]));
            int rootB = ds.findSet(get<1>(edges[i]));
            
            if(rootA != rootB) {
                adjList[rootA].push_back(i);
                adjList[rootB].push_back(i);
            } else {
                edgeType[get<3>(edges[i])] = "none";
            }
        }
        
        // Procesar componentes
        for(int i = currentEdge; i < groupEnd; i++) {
            int rootA = ds.findSet(get<0>(edges[i]));
            int rootB = ds.findSet(get<1>(edges[i]));
            
            if(timeStamp[rootA] <= currentTime) {
                findBridges(rootA, -1, 0, adjList, edges, ds,
                          earliest, timeStamp, discoveryDepth, edgeType, currentTime);
            }
            if(timeStamp[rootB] <= currentTime) {
                findBridges(rootB, -1, 0, adjList, edges, ds,
                          earliest, timeStamp, discoveryDepth, edgeType, currentTime);
            }
        }
        
        // Unir componentes y limpiar
        for(int i = currentEdge; i < groupEnd; i++) {
            int rootA = ds.findSet(get<0>(edges[i]));
            int rootB = ds.findSet(get<1>(edges[i]));
            ds.unionByRank(rootA, rootB);
            adjList[rootA].clear();
            adjList[rootB].clear();
        }
        
        currentEdge = groupEnd;
        currentTime++;
    }
    
    for(const string& type : edgeType) {
        cout << type << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int vertices, edgeCount;
    cin >> vertices >> edgeCount;
    
    vector<tuple<int,int,int,int>> edges;
    edges.reserve(edgeCount);
    
    for(int i = 0; i < edgeCount; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        edges.emplace_back(from - 1, to - 1, weight, i);
    }
    
    processEdgeGroups(edges, vertices, edgeCount);
    return 0;
}