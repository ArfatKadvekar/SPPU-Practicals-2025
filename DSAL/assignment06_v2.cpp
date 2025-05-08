#include <iostream>
using namespace std;

class Node {
    int data;
    Node* next;

public:
    Node(int d) {
        data = d;
        next = nullptr;
    }

    int getData() { return data; }
    Node* getNext() { return next; }
    void setNext(Node* n) { next = n; }

    friend class Graph;
};

class Graph {
    Node* head[20];
    bool visited[20];

public:
    Graph(int v) {
        for (int i = 1; i <= v; i++) {
            head[i] = new Node(i); // create dummy head node for each vertex
            visited[i] = false;
        }
    }

    void create(int edges) {
        int src, dest;
        for (int i = 1; i <= edges; i++) {
            cout << "Enter source: ";
            cin >> src;
            cout << "Enter destination: ";
            cin >> dest;

            Node* temp = head[src];
            while (temp->next != nullptr)
                temp = temp->next;
            temp->setNext(new Node(dest));

            temp = head[dest];
            while (temp->next != nullptr)
                temp = temp->next;
            temp->setNext(new Node(src)); // for undirected graph
        }
    }

    void displayGraph(int vertices) {
        cout << "\nGraph (Adjacency List):\n";
        for (int i = 1; i <= vertices; i++) {
            cout << "Vertex " << i << " -> ";
            Node* temp = head[i]->getNext(); // skip dummy head
            while (temp != nullptr) {
                cout << temp->getData() << " ";
                temp = temp->getNext();
            }
            cout << endl;
        }
    }

    void BFS(int start) {
        int queue[20], front = 0, rear = 0;
        queue[++rear] = start;
        visited[start] = true;

        cout << "BFS: ";
        while (front < rear) {
            int curr = queue[++front];
            cout << curr << " ";

            Node* temp = head[curr]->getNext();
            while (temp != nullptr) {
                int val = temp->getData();
                if (!visited[val]) {
                    queue[++rear] = val;
                    visited[val] = true;
                }
                temp = temp->getNext();
            }
        }
        cout << endl;
    }

    void DFS(int v, bool visited[]) {
        cout << v << " ";
        visited[v] = true;

        Node* temp = head[v]->getNext();
        while (temp != nullptr) {
            int nextNode = temp->getData();
            if (!visited[nextNode])
                DFS(nextNode, visited);
            temp = temp->getNext();
        }
    }
};

int main() {
    int vertices, edges;
    cout << "Enter number of vertices: ";
    cin >> vertices;

    Graph g(vertices);

    cout << "Enter number of edges: ";
    cin >> edges;
    g.create(edges);

    g.displayGraph(vertices);

    int bfsStart;
    cout << "\nEnter starting vertex for BFS: ";
    cin >> bfsStart;
    g.BFS(bfsStart);

    int dfsStart;
    bool visited[21] = { false };
    cout << "\nEnter starting vertex for DFS: ";
    cin >> dfsStart;
    cout << "DFS: ";
    g.DFS(dfsStart, visited);
    cout << endl;

    return 0;
}
