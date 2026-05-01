#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

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

vector<tuple<int, int, int>> Kruskal(vector<tuple<int, int, int>>& edges, int n) {
    sort(edges.begin(), edges.end(), [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
        return get<2>(a) < get<2>(b);
    });

    vector<int> link(n + 1);
    vector<int> size(n + 1, 1);

    for (int i = 1; i <= n; i++) {
        link[i] = i;
    }

    vector<tuple<int, int, int>> T;

    for (const auto& edge : edges) {
        int a = get<0>(edge);
        int b = get<1>(edge);

        if (!same(a, b, link)) {
            union_(a, b, link, size);
            T.push_back(edge);
            if (T.size() == n - 1) break; // Stop if we have enough edges
        }
    }

    return T;
}

int main() {
    vector<tuple<int, int, int>> edges;

    int n, m;
    cin >> n >> m; // Corrección en la lectura

    while (m-- > 0) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<tuple<int, int, int>> T = Kruskal(edges, n);

    // Imprimir el resultado
    cout << "Aristas del árbol de expansión mínima:" << endl;
    for (const auto& edge : T) {
        cout << get<0>(edge) << " - " << get<1>(edge) << " (peso " << get<2>(edge) << ")" << endl;
    }

    return 0;
}
