#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

class Graph {
    int mat[10][10];
    int v;
    map<string, int> nameToIndex;
    vector<string> indexToName;

public:
    void readFromFile(const string& filename) {
        ifstream fin(filename);
        if (!fin) {
            cout << "Unable to open file.\n";
            exit(1);
        }

        fin >> v;
        string name;
        for (int i = 0; i < v; i++) {
            fin >> name;
            nameToIndex[name] = i;
            indexToName.push_back(name);
        }

        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                fin >> mat[i][j];

        fin.close();
    }

    void display() {
        cout << "\nAdjacency Matrix:\n";
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    void prims(int start) {
        int count = 1, A[20], visited[20] = {0};
        int min, t1 = -1, t2 = -1, wt = 0, result[20][20] = {0};

        A[0] = start;
        visited[start] = 1;

        while (count < v) {
            min = 9999;
            for (int i = 0; i < count; i++) {
                for (int j = 0; j < v; j++) {
                    if (mat[A[i]][j] != 0 && visited[j] == 0 && mat[A[i]][j] < min) {
                        min = mat[A[i]][j];
                        t1 = A[i];
                        t2 = j;
                    }
                }
            }

            if (!visited[t2]) {
                visited[t2] = 1;
                result[t1][t2] = result[t2][t1] = min;
                wt += min;
                A[count++] = t2;
            }
            mat[t1][t2] = mat[t2][t1] = 0;  // Prevent re-selection
        }

        cout << "\nMinimum Spanning Tree (MST):\n";
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                if (result[i][j] != 0)
                    cout << indexToName[i] << " - " << indexToName[j] << ": " << result[i][j] << endl;

        cout << "Total Weight of MST: " << wt << endl;
    }

    int getIndexFromName(const string& name) {
        if (nameToIndex.find(name) != nameToIndex.end())
            return nameToIndex[name];
        else
            return -1;
    }
};

int main() {
    Graph g;
    string filename = "input.txt";
    g.readFromFile(filename);
    g.display();

    string startName;
    cout << "\nEnter starting office name: ";
    cin >> startName;

    int startIndex = g.getIndexFromName(startName);
    if (startIndex == -1) {
        cout << "Invalid office name.\n";
        return 1;
    }

    g.prims(startIndex);
    return 0;
}
