#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
private:
    vector<int> ranks;
    vector<int> parent;

public:
    DisjointSet(int size) {
        ranks.resize(size, 0);
        parent.resize(size);
        for(int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }

    int findSet(int v) {
        if (v == parent[v]) return v;
        return parent[v] = findSet(parent[v]);
    }

    void unite(int u, int v) {
        int uRoot = findSet(u);
        int vRoot = findSet(v);

        if (uRoot == vRoot) return;

        if (ranks[uRoot] < ranks[vRoot]) {
            parent[uRoot] = vRoot;
        } else if(ranks[uRoot] > ranks[vRoot]) {
            parent[vRoot] = uRoot;
        } else {
            parent[vRoot] = uRoot;
            ranks[uRoot]++;
        }
    }
};

class AGMclassifier {
private:
    int vertices, edges, currentTime;
    vector<tuple<int,int,int,int>> edges_list; // (u, v, weight, original_index)
    DisjointSet d;
    vector<vector<int>> tempGraph;
    vector<int> vTime;
    vector<int> dTime;
    vector<int> lTime;
    vector<string> res;


    void DFSBridge(int current, int parent = -1, int depth = 0) {
        lTime[current] = depth;
        dTime[current] = depth;
        vTime[current] = currentTime + 1;

        for (int i = 0; i < tempGraph[current].size(); i++) {
            if (tempGraph[current][i] == parent) continue;

            int idxEdge = tempGraph[current][i];
            int u = d.findSet(get<0>(edges_list[idxEdge]));
            int v = d.findSet(get<1>(edges_list[idxEdge]));
            int neighbor = (u == current) ? v : u;

            if (vTime[neighbor] > currentTime) {
                lTime[current] = min(lTime[current], dTime[neighbor]);
            } else {
                DFSBridge(neighbor, tempGraph[current][i], depth + 1);
                lTime[current] = min(lTime[current], lTime[neighbor]);
            }

            if (lTime[neighbor] > dTime[current]) {
                res[get<3>(edges_list[tempGraph[current][i]])] = "any";
            }
        }
    }

    void processEdgeGroup(int start, int end) {
        // Build temporary graph for current weight group
        int uRep;
        int vRep;
        int u;
        int v;
        for (int j = start; j < end; j++) {
            u = get<0>(edges_list[j]);
            v = get<1>(edges_list[j]);
            uRep = d.findSet(u);
            vRep = d.findSet(v);

            if (uRep != vRep) {
                tempGraph[uRep].push_back(j);
                tempGraph[vRep].push_back(j);
            } else {
                int eIndex = get<3>(edges_list[j]);
                res[eIndex] = "none";
            }
        }

        // Find bridges using Tarjan's algorithm
        for (int j = start; j < end; j++) {
            u = get<0>(edges_list[j]);
            v = get<1>(edges_list[j]);
            uRep = d.findSet(u);
            vRep = d.findSet(v);

            if (vTime[uRep] <= currentTime) {
                DFSBridge(uRep);
            }
            if (vTime[vRep] <= currentTime) {
                DFSBridge(vRep);
            }
        }

        // Unite components and cleanup
        for (int j = start; j < end; j++) {
            u = get<0>(edges_list[j]);
            v = get<1>(edges_list[j]);
            uRep = d.findSet(u);
            vRep = d.findSet(v);

            d.unite(uRep, vRep);
            tempGraph[uRep].clear();
            tempGraph[vRep].clear();
        }
    }

public:
    AGMclassifier(int v, int e) :
    vertices(v),
    edges(e),
    currentTime(0),
    d(v),
    tempGraph(v),
    res(e, "at least one"),
    dTime(v),
    lTime(v),
    vTime(v) {}

    void addEdge(int u, int v, int weight, int index) {
        edges_list.emplace_back(u, v, weight, index);
    }

    void solve() {
        // Sort edges by weight
        sort(edges_list.begin(), edges_list.end(),[](const auto& a, const auto& b) { return get<2>(a) < get<2>(b); });

        // Process edges in groups of same weight
        for (int i = 0; i < edges; ) {
            int j = i;
            while (j < edges && get<2>(edges_list[j]) == get<2>(edges_list[i]))
                j++;

            processEdgeGroup(i, j);
            i = j;
            currentTime++;
        }
    }

    void printAnswers() {
        for (const string& r : res) {
            cout << r << endl;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    AGMclassifier agm(n, m);

    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        agm.addEdge(--u, --v, w, i);
    }

    agm.solve();
    agm.printAnswers();

    return 0;
}