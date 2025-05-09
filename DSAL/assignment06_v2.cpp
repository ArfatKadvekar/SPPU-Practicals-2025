#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <sstream>  // For stringstream

using namespace std;

class Graph {
    map<string, vector<string>> adj;

public:
    // Add edge between two landmarks (undirected)
    void addEdge(string u, string v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Display the adjacency list
    void display() {
        cout << "\nGraph (Adjacency List):\n";
        for (auto& pair : adj) {
            cout << pair.first << " -> ";
            for (string neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // BFS Traversal
    void BFS(string start) {
        set<string> visited;
        queue<string> q;

        visited.insert(start);
        q.push(start);

        cout << "\nBFS: ";
        while (!q.empty()) {
            string curr = q.front();
            q.pop();
            cout << curr << " ";

            for (string neighbor : adj[curr]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // DFS Helper
    void DFSHelper(string node, set<string>& visited) {
        visited.insert(node);
        cout << node << " ";

        for (string neighbor : adj[node]) {
            if (visited.find(neighbor) == visited.end()) {
                DFSHelper(neighbor, visited);
            }
        }
    }

    // DFS Traversal
    void DFS(string start) {
        set<string> visited;
        cout << "\nDFS: ";
        DFSHelper(start, visited);
        cout << endl;
    }
};

int main() {
    Graph g;
    int edgeCount;
    string u, v, line;

    cout << "Enter number of connections between landmarks: ";
    cin >> edgeCount;
    cin.ignore();  // Ignore the newline character left by cin

    // Getting edges from the user
    for (int i = 0; i < edgeCount; i++) {
        cout << "\nEnter source landmark: ";
        getline(cin, u);  // Take the source landmark as input

        cout << "Enter connected landmarks (separated by commas): ";
        getline(cin, line);  // Take multiple connected landmarks in one line

        // Use stringstream to split the input by commas
        stringstream ss(line);
        while (getline(ss, v, ',')) {  // Split based on commas
            g.addEdge(u, v);  // Add an edge between source and each destination
        }
    }

    g.display();

    string startBFS, startDFS;
    cout << "\nEnter starting landmark for BFS: ";
    getline(cin, startBFS);  // Take full name for BFS

    g.BFS(startBFS);

    cout << "\nEnter starting landmark for DFS: ";
    getline(cin, startDFS);  // Take full name for DFS

    g.DFS(startDFS);

    return 0;
}
