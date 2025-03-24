#include<iostream>
using namespace std;

class Graph {
public:
    void adj_matrix(int mat[5][5], int i, int j, int w) {
        mat[i][j] = w;
        mat[j][i] = w;
    }

    void display(int mat[5][5], int v) {
        for (int i = 1; i <= v; i++) {
            for (int j = 1; j <= v; j++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    void prims(int G[5][5], int v) {
        int count = 1;
        int A[20];
        int min = 9999, t1, t2, wt = 0;
        int visited[20] = {0};
        int result[20][20] = {0};
        
        A[0] = 1;
        visited[1] = 1;

        while (count < v) {
            min = 9999;
            for (int i = 0; i < count; i++) {
                for (int j = 1; j <= v; j++) {
                    if (visited[i] == 1 && G[A[i]][j] != 0 && visited[j] == 0 && G[A[i]][j] < min) {
                        min = G[A[i]][j];
                        t1 = A[i];
                        t2 = j;
                    }
                }
            }

            if (visited[t2] == 0) {
                visited[t2] = 1;
                result[t1][t2] = result[t2][t1] = min;
                wt += min;
                A[count++] = t2;
            }

            G[t1][t2] = G[t2][t1] = 0;
        }

        cout << "Minimum Spanning Tree (MST):" << endl;
        for (int i = 1; i <= v; i++) {
            for (int j = 1; j <= v; j++) {
                if (result[i][j] != 0)
                    cout << i << " - " << j << ": " << result[i][j] << endl;
            }
        }
        cout << "Total Weight of MST: " << wt << endl;
    }
};

int main() {
    Graph g;
    int mat[5][5] = {0}, v, w;

    cout << "Enter the number of vertices: ";
    cin >> v;

    for (int i = 1; i <= v; i++) {
        for (int j = i + 1; j <= v; j++) {
            cout << "Enter weight for edge " << i << " - " << j << ": ";
            cin >> w;
            g.adj_matrix(mat, i, j, w);
        }
    }

    cout << "Adjacency Matrix:" << endl;
    g.display(mat, v);

    g.prims(mat, v);

    return 0;
}
