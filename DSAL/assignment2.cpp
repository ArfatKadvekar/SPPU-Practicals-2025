#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST
{
    Node *root;

public:
    BST() : root(nullptr) {}

    void create(int val)
    {
        if (root == nullptr)
        {
            root = new Node(val);
        }
        else
        {
            insert(root, val);
        }
    }

    Node *insert(Node *temp, int val)

    {
        if (temp == nullptr)
        {
            Node *newNode = new Node(val);
            return newNode;
        }
        else if (temp->data > val)
        {
            temp->left = insert(temp->left, val);
        }
        else
        {
            temp->right = insert(temp->right, val);
        }
        return temp;
    }

    void swapRoles(Node *temp)
    {
        if (temp == nullptr)
            return;
        swap(temp->left, temp->right);
        swapRoles(temp->left);
        swapRoles(temp->right);
    }

    int height()
    {
        return height(root);
    }

    int height(Node *temp)
    {
        if (temp == nullptr)
            return 0;
        int leftHeight = height(temp->left);
        int rightHeight = height(temp->right);
        return max(leftHeight, rightHeight) + 1;
    }
        int printTree(Node * n, int v = 0)
        {
            if (n != NULL)
            {
                int i;
                for (i = 1; i < v; i++)
                    cout << "        ";
                for (int j = 0; j < (v - i + 1); j++)
                    cout << "|-----> ";
                cout << n->data << "\n";
                int a = printTree(n->left, v + 1);
                int b = printTree(n->right, v + 1);
                return max(a, b);
            }
            return v;
        }

        Node *getRoot()
        {
            return root;
        }
    };

    int main()
    {
        BST tree;
        int choice;
        while (true)
        {
            cout << "-----------------------------------------------------------\n";
            cout << "1. Create a node. \n";
            cout << "2. Display tree.\n";
            cout << "3. Swap the left and right children..\n";
            cout << "4. Height of the tree.\n";
            cout << "5. Print all three traversals.\n";
            cout << "0. Exit.\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << "Enter the data: ";
                int d;
                cin >> d;
                tree.create(d);
                break;
            case 2:
                tree.printTree(tree.getRoot());
                break;
            case 3:
                tree.swapRoles(tree.getRoot());
                cout << "Left and right children swapped." << endl;
                break;
            case 4:
                cout << "Height of the tree is: " << tree.height() << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        }
        return 0;
    }