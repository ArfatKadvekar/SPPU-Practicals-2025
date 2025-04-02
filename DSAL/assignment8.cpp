#include <iostream>
#include <climits>
using namespace std;

class node {
    int data;
    node *lchild, *rchild;
    friend class obst;
public:
    node(int x) {
        data = x;
        lchild = rchild = nullptr;
    }
};

class obst {
    node *root;
    double w[100][100];
    double c[100][100];
    int r[100][100];

public:
    obst() {
        root = nullptr;
    }

    void calculate_wt(double *p, double *q, int n) {
        for (int i = 0; i < n; i++) {
            w[i][i] = q[i];
            r[i][i] = c[i][i] = 0;
            w[i][i+1] = q[i] + q[i+1] + p[i+1];
            r[i][i+1] = i+1;
            c[i][i+1] = w[i][i+1];
        }

        w[n][n] = q[n];
        r[n][n] = c[n][n] = 0;

        for (int m = 2; m <= n; m++) {
            for (int i = 0; i <= n - m; i++) {
                int j = i + m;
                w[i][j] = w[i][j-1] + p[j] + q[j];
                
                double min = INT_MAX;
                for (int i1 = i + 1; i1 < j; i1++) {
                    double sum1 = c[i][i1 - 1] + c[i1][j];
                    if (sum1 < min) {
                        min = sum1;
                        r[i][j] = i1;
                    }
                }
                c[i][j] = w[i][j] + min;
            }
        }

        root = create_tree(0, n);
    }

    node* create_tree(int i, int j) {
        if (i >= j) return nullptr;
        int k = r[i][j];
        node* newNode = new node(k);
        newNode->lchild = create_tree(i, k - 1);
        newNode->rchild = create_tree(k, j);
        return newNode;
    }

        void print_tree(node* root) {
        if (root == nullptr) return;

        cout << "Node: " << root->data << endl; 
        print_tree(root->lchild);  
        print_tree(root->rchild);  
    }

    void print() {
        print_tree(root);
    }
};

int main() {
    obst ob;
    int n;

    cout << "Enter the number of keys: ";
    cin >> n;

    double p[100], q[100];

    cout << "Enter the probabilities of successful searches (p):\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    cout << "Enter the probabilities of unsuccessful searches (q):\n";
    for (int i = 0; i <= n; i++) {
        cin >> q[i];
    }

    ob.calculate_wt(p, q, n);
    
    cout << "The Optimal Binary Search Tree (OBST) structure:\n";
    ob.print();

    return 0;
}
