#include <bits/stdc++.h>
using namespace std;

class ComponentTracker {
private:
    struct Node {
        size_t parent;
        unsigned int treeDepth;
        explicit Node(size_t id) : parent(id), treeDepth(0) {}
    };
    
    vector<Node> forest;
    
public:
    explicit ComponentTracker(size_t size) : forest(size, Node(0)) {
        for (size_t i = 0; i < size; ++i) {
            forest[i].parent = i;
        }
    }
    
    size_t trace(size_t element) {
        vector<size_t> path;
        while (element != forest[element].parent) {
            path.push_back(element);
            element = forest[element].parent;
        }
        
        for (size_t node : path) {
            forest[node].parent = element;
        }
        return element;
    }
    
    bool combine(size_t elem1, size_t elem2) {
        size_t root1 = trace(elem1);
        size_t root2 = trace(elem2);
        
        if (root1 == root2) return false;
        
        if (forest[root1].treeDepth < forest[root2].treeDepth) {
            forest[root1].parent = root2;
        } else {
            forest[root2].parent = root1;
            if (forest[root1].treeDepth == forest[root2].treeDepth) {
                forest[root1].treeDepth++;
            }
        }
        return true;
    }
};

class NetworkAnalyzer {
private:
    struct Connection {
        size_t endpoint1;
        size_t endpoint2;
        int capacity;
        size_t sequence;
        
        Connection(size_t e1, size_t e2, int cap, size_t seq)
            : endpoint1(e1), endpoint2(e2), capacity(cap), sequence(seq) {}
    };
    
    struct TemporalMark {
        size_t timestamp;
        size_t depth;
        size_t earliest;
        
        TemporalMark() : timestamp(0), depth(0), earliest(0) {}
    };
    
    vector<Connection> network;
    vector<string> criticality;
    size_t nodeCount;
    
    void processNetworkSegment(
        size_t current,
        size_t incomingEdge,
        size_t levelDepth,
        const vector<vector<size_t>>& temporalGraph,
        ComponentTracker& tracker,
        vector<TemporalMark>& marks,
        size_t period
    ) {
        TemporalMark& currentMark = marks[current];
        currentMark.timestamp = period + 1;
        currentMark.depth = levelDepth;
        currentMark.earliest = levelDepth;
        
        for (size_t edgeIndex : temporalGraph[current]) {
            if (edgeIndex == incomingEdge) continue;
            
            const Connection& conn = network[edgeIndex];
            size_t root1 = tracker.trace(conn.endpoint1);
            size_t root2 = tracker.trace(conn.endpoint2);
            size_t next = (root1 == current) ? root2 : root1;
            
            if (marks[next].timestamp <= period) {
                processNetworkSegment(next, edgeIndex, levelDepth + 1,
                    temporalGraph, tracker, marks, period);
                currentMark.earliest = min(currentMark.earliest, 
                    marks[next].earliest);
            } else {
                currentMark.earliest = min(currentMark.earliest, 
                    marks[next].depth);
            }
            
            if (marks[next].earliest > currentMark.depth) {
                criticality[conn.sequence] = "any";
            }
        }
    }

public:
    NetworkAnalyzer(size_t nodes, size_t connections) 
        : nodeCount(nodes), criticality(connections, "at least one") {}
        
    void registerConnection(size_t point1, size_t point2, 
        int bandwidth, size_t index) {
        network.emplace_back(point1, point2, bandwidth, index);
    }
    
    void evaluateRedundancy() {
        sort(network.begin(), network.end(),
            [](const Connection& a, const Connection& b) {
                return a.capacity < b.capacity;
            });
            
        vector<TemporalMark> marks(nodeCount);
        vector<vector<size_t>> temporalGraph(nodeCount);
        ComponentTracker tracker(nodeCount);
        
        size_t timeframe = 0;
        size_t currentConn = 0;
        
        while (currentConn < network.size()) {
            size_t segmentEnd = currentConn;
            int currentCapacity = network[currentConn].capacity;
            
            while (segmentEnd < network.size() && 
                   network[segmentEnd].capacity == currentCapacity) {
                segmentEnd++;
            }
            
            // Construct temporal network segment
            for (size_t i = currentConn; i < segmentEnd; i++) {
                const Connection& conn = network[i];
                size_t root1 = tracker.trace(conn.endpoint1);
                size_t root2 = tracker.trace(conn.endpoint2);
                
                if (root1 != root2) {
                    temporalGraph[root1].push_back(i);
                    temporalGraph[root2].push_back(i);
                } else {
                    criticality[conn.sequence] = "none";
                }
            }
            
            // Analyze connectivity
            for (size_t i = currentConn; i < segmentEnd; i++) {
                const Connection& conn = network[i];
                size_t root1 = tracker.trace(conn.endpoint1);
                size_t root2 = tracker.trace(conn.endpoint2);
                
                for (size_t root : {root1, root2}) {
                    if (marks[root].timestamp <= timeframe) {
                        processNetworkSegment(root, SIZE_MAX, 0,
                            temporalGraph, tracker, marks, timeframe);
                    }
                }
            }
            
            // Merge and cleanup
            for (size_t i = currentConn; i < segmentEnd; i++) {
                const Connection& conn = network[i];
                size_t root1 = tracker.trace(conn.endpoint1);
                size_t root2 = tracker.trace(conn.endpoint2);
                
                tracker.combine(root1, root2);
                temporalGraph[root1].clear();
                temporalGraph[root2].clear();
            }
            
            currentConn = segmentEnd;
            timeframe++;
        }
        
        for (const string& status : criticality) {
            cout << status << '\n';
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    size_t nodes, connections;
    cin >> nodes >> connections;
    
    NetworkAnalyzer analyzer(nodes, connections);
    
    for (size_t i = 0; i < connections; i++) {
        size_t p1, p2;
        int bandwidth;
        cin >> p1 >> p2 >> bandwidth;
        analyzer.registerConnection(p1 - 1, p2 - 1, bandwidth, i);
    }
    
    analyzer.evaluateRedundancy();
    return 0;
}