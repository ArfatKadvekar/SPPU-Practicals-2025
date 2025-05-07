#include <iostream>
using namespace std;

class Node
{
    int Nodeno;
    Node *next;

public:
    Node(int n)
    {
        Nodeno = n;
        next = nullptr;
    }

    int getData() { return Nodeno; }
    Node *getNext() { return next; }
    void setNext(Node *nxt) { next = nxt; }

    friend class Graph;
};

class Graph
{
    Node *head[20];
    bool visited[20];

public:
    Graph(int v1)
    {
        for (int i = 1; i <= v1; i++)
        {
            head[i] = new Node(i);
            visited[i] = false;
        }
    }

    void create(int n)
    {
        Node *temp;
        Node *q;
        int source, dest;
        for (int i = 1; i <= n; i++)
        {
            cout << "Enter source: ";
            cin >> source;
            cout << "Enter destination: ";
            cin >> dest;

            temp = head[source];
            if (temp == nullptr)
            {
                head[source] = new Node(dest);
            }
            else
            {
                while (temp->next != nullptr)
                {
                    temp = temp->next;
                }
                temp->setNext(new Node(dest));
            }

            temp = head[dest];
            if (temp == nullptr)
            {
                head[dest] = new Node(source);
            }
            else
            {
                while (temp->next != nullptr)
                {
                    temp = temp->next;
                }
                temp->setNext(new Node(source));
            }
        }
    }

    void BFS(int v1)
    {
        int Q[20], f = 0, r = 1;
        Q[r] = v1;
        visited[v1] = true;

        while (f < r)
        {
            int x = Q[++f];
            cout << x << " ";

            Node *temp = head[x];
            while (temp != nullptr)
            {
                if (!visited[temp->getData()])
                {
                    Q[++r] = temp->getData();
                    visited[temp->getData()] = true;
                }
                temp = temp->getNext();
            }
        }
    }

    void DFS(int v1, bool visited[])
    {
        Node *temp = head[v1];
        cout << v1 << " ";
        visited[v1] = true;
        while (temp != nullptr)
        {
            if (!visited[temp->getData()])
            {
                DFS(temp->getData(), visited);
            }
            temp = temp->getNext();
        }
    }

    void displayGraph(int numVertices)
    {
        cout << "\nGraph Visualization (ASCII Art):\n";
        for (int i = 1; i <= numVertices; i++)
        {
            cout << "Vertex " << i << " ";
            Node *temp = head[i]->getNext();
            if (temp != nullptr)
            {
                cout << "-->";
                while (temp != nullptr)
                {
                    cout << " " << temp->getData();
                    temp = temp->getNext();
                }
            }
            cout << endl;
        }
    }
};

int main()
{
    int numVertices, numEdges;

    cout << "Enter number of vertices: ";
    cin >> numVertices;

    Graph g(numVertices);

    cout << "Enter number of edges: ";
    cin >> numEdges;

    g.create(numEdges);

    g.displayGraph(numVertices);

    int startVertex;
    cout << "\nEnter starting vertex for BFS: ";
    cin >> startVertex;

    cout << "BFS traversal starting from vertex " << startVertex << ": ";
    g.BFS(startVertex);

    bool visited[numVertices + 1] = {false};
    int dstartVertex;
    cout << "\nEnter starting vertex for DFS: ";
    cin >> dstartVertex;

    cout << "DFS traversal starting from vertex " << dstartVertex << ": ";
    g.DFS(dstartVertex, visited);
    cout <<endl;

    return 0;
}