#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <unordered_set>

using namespace std;

class UnionFind {
private:
    vector<int> parent, rank;

public:
    UnionFind(int n) : parent(n + 1), rank(n + 1, 0) {
        for (int i = 0; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return false;

        if (rank[rootX] < rank[rootY]) {
            swap(rootX, rootY);
        }
        parent[rootY] = rootX;
        
        if (rank[rootX] == rank[rootY]) {
            rank[rootX]++;
        }
        return true;
    }
};

class GraphAnalyzer {
private:
    vector<vector<int>> graph;
    vector<int> status, parent;
    vector<int> backEdgeUpperCount, backEdgeLowerCount;
    vector<tuple<int,int>> backEdges;
    vector<vector<int>> treeEdges;

    bool checkUniqueEdge(int u, int v) {
        int count = 0;
        for (int neighbor : graph[v]) {
            if (neighbor == u) {
                count++;
                if (count >= 2) return false;
            }
        }
        return true;
    }

    void dfs(int v, int p = -1) {
        status[v] = 1;
        for (int u : graph[v]) {
            if (status[u] == 0) {
                treeEdges[v].push_back(u);
                parent[u] = v;
                dfs(u, v);
            } else if (u != parent[v]) {
                if (status[u] == 1) {
                    backEdgeUpperCount[u]++;
                    backEdgeLowerCount[v]++;
                    backEdges.push_back({v, u});
                }
            }
        }
        status[v] = 2;
    }

    int countCoverage(int v, int p) {
        static vector<int> memo(graph.size(), -1);
        if (memo[v] != -1) return memo[v];

        int result = 0;
        for (int child : treeEdges[v]) {
            if (child != p) {
                result += countCoverage(child, v);
            }
        }
        
        result -= backEdgeUpperCount[v];
        result += backEdgeLowerCount[v];

        return memo[v] = result;
    }

public:
    void processGraph(vector<tuple<int, int, int>>& edges, map<tuple<int,int,int>, string>& classification, int n) {
        sort(edges.begin(), edges.end(), 
            [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
                return get<2>(a) < get<2>(b);
            });

        UnionFind uf(n);
        vector<tuple<int, int, int>> mst;

        for (int i = 0; i < edges.size(); ++i) {
            int a = get<0>(edges[i]);
            int b = get<1>(edges[i]);
            int w = get<2>(edges[i]);

            vector<tuple<int, int, int>> sameWeightEdges;
            sameWeightEdges.push_back(edges[i]);

            while (i < edges.size() - 1 && w == get<2>(edges[i + 1])) {
                sameWeightEdges.push_back(edges[i + 1]);
                ++i;
            }

            graph = vector<vector<int>>(n + 1);
            status.assign(n + 1, 0);
            parent.assign(n + 1, -1);
            treeEdges.assign(n + 1, vector<int>());
            backEdgeUpperCount.assign(n + 1, 0);
            backEdgeLowerCount.assign(n + 1, 0);
            backEdges.clear();

            // Construir grafo y preparar para análisis
            for (const auto& edge : sameWeightEdges) {
                int u = get<0>(edge);
                int v = get<1>(edge);
                int repU = uf.find(u);
                int repV = uf.find(v);

                if (repU != repV) {
                    graph[repU].push_back(repV);
                    graph[repV].push_back(repU);
                }
            }

            // DFS y análisis de aristas
            for (int j = 1; j <= n; ++j) {
                if (status[j] == 0) {
                    dfs(j, -1);
                }
            }

            // Clasificar aristas
            for (auto& edge : sameWeightEdges) {
                int u = get<0>(edge);
                int v = get<1>(edge);
                int repU = uf.find(u);
                int repV = uf.find(v);

                if (repU == repV) {
                    classification[edge] = "none";
                } else {
                    int elem = repV;
                    for (int treeAdj : treeEdges[repV]) {
                        if (treeAdj == repU) elem = repU;
                    }

                    bool isBackEdge = 
                        find(backEdges.begin(), backEdges.end(), make_tuple(repU, repV)) != backEdges.end() ||
                        find(backEdges.begin(), backEdges.end(), make_tuple(repV, repU)) != backEdges.end();

                    if (countCoverage(elem, parent[elem]) == 0 && 
                        checkUniqueEdge(repU, repV) && 
                        !isBackEdge) {
                        classification[edge] = "any";
                    } else {
                        classification[edge] = "at least one";
                    }
                }
            }

            // Construir árbol de expansión mínima
            for (const auto& edge : sameWeightEdges) {
                int u = get<0>(edge);
                int v = get<1>(edge);
                if (uf.unionSet(u, v)) {
                    mst.push_back(edge);
                    if (mst.size() == n - 1) break;
                }
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges;

    while (m--) {
        int a, b, w;
        cin >> a >> b >> w;
        edges.push_back({a, b, w});
    }

    map<tuple<int, int, int>, string> classification;
    GraphAnalyzer analyzer;
    analyzer.processGraph(edges, classification, n);

    for (const auto& edge : edges) {
        cout << (classification.count(edge) ? classification[edge] : "none") << endl;
    }

    return 0;
}