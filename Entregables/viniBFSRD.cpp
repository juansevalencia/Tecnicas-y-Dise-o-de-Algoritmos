#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <string>
#include <climits>
using namespace std;

bool bellman_ford_detect_negative_cycle(int n, const vector<vector<pair<int, int>>>& graph) {

    vector<long long> dist(n + 1, INT_MAX);
    dist[0] = 0;

    for (int i = 0; i < n; ++i) {
        for (int u = 0; u < graph.size(); ++u) {
            for (const auto& edge : graph[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (dist[u] != numeric_limits<long long>::max() && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    for (int u = 0; u < graph.size(); ++u) {
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] != numeric_limits<long long>::max() && dist[u] + weight < dist[v]) {
                return true; 
            }
        }
    }

    return false; 
}

int main() {
    vector<string> results;
    string line;

    while (getline(cin, line)) {
        stringstream ss(line);
        vector<string> input_lines;
        string temp;

        while (ss >> temp) {
            input_lines.push_back(temp);
        }

        if (input_lines.size() == 1 && input_lines[0] == "0") {
            break;
        } else {
            int n = stoi(input_lines[0]);
            int m = stoi(input_lines[1]);

            vector<vector<pair<int, int>>> graph(n + 1);

            for (int i = 0; i < m; ++i) {
                getline(cin, line);
                stringstream ss_edge(line);
                int s_i, n_i, k_i;
                string o_i;
                ss_edge >> s_i >> n_i >> o_i >> k_i;

                int end_vertex = s_i + n_i;  // nodo destino
                if (o_i == "lt") {
                    int weight = k_i - 1;
                    graph[s_i - 1].emplace_back(end_vertex, weight);
                } else if (o_i == "gt") {
                    int weight = -(k_i + 1);
                    graph[end_vertex].emplace_back(s_i - 1, weight);
                }
            }

            if (bellman_ford_detect_negative_cycle(n, graph)) {
                results.push_back("successful conspiracy");
            } else {
                results.push_back("lamentable kingdom");
            }
        }
    }

    for (const auto& result : results) {
        cout << result << endl;
    }

    return 0;
}

