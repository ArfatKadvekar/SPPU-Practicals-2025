#include<iostream>
#include<fstream>
using namespace std;

class Graph{
    int mat[10][10];
    int v;
public:
    void readFromFile(const string& filename){
        ifstream fin(filename);
        if(!fin){
            cout << "Unable to read the file\n";
            exit(1);
        }
        fin >> v;
        for(int i = 0; i < v; i++){
            for(int j = 0; j < v; j++){
                fin >> mat[i][j];
            }
        }
        fin.close();
    }
    void display(){
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }
    void prims(int n){
        int count = 1, A[20], visited[20] = {0};
        int min, t1, t2, wt = 0, result[20][20] = {0};

        A[0] = n;
        visited[n] = 1;

        while(count < v){
            min = 9999;
            for(int i = 0; i < count; i++){
                for (int j = 0; j < v; j++)
                {
                    if(mat[A[i]][j] != 0 && visited[j]== 0 && mat[A[i]][j] < min){
                        min = mat[A[i]][j];
                        t1 = A[i];
                        t2 = j;
                    } 
                }
                
            }
            if(!visited[t2]){
                visited[t2] = 1;
                result[t1][t2] = result[t2][t1] = min;
                wt += min;
                A[count++] = t2;
            }
            mat[t1][t2] = mat[t2][t1] = 0; //avoid reselection
        }

        cout << "Minimum Spanning Tree (MST):\n";
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                if (result[i][j] != 0)
                    cout << i << " - " << j << ": " << result[i][j] << endl;

        cout << "Total Weight of MST: " << wt << endl;
    }
};
int main(){
    Graph g;
    g.readFromFile("input.txt");
    g.display();
    g.prims(0);
    return 0;
}