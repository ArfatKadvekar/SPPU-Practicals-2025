#include <iostream>
using namespace std;

class Node
{

    int data;
    Node *left;
    Node *right;

public:
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
    friend class BST;
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

    void ascending(Node *temp)
    {
        if (temp == nullptr)
            return;
        ascending(temp->left);
        cout << temp->data << " ";
        ascending(temp->right);
    }

    void descending(Node *temp)
    {
        if (temp == nullptr)
            return;
        descending(temp->right);
        cout << temp->data << " ";
        descending(temp->left);
    }

    Node *search(int key, Node *temp)
    {
        if (temp == nullptr || temp->data == key)
        {
            return temp;
        }

        if (key < temp->data)
        {
            return search(key, temp->left);
        }
        return search(key, temp->right);
    }

    Node *deleteNode(Node *temp, int key)
    {
        if (temp == nullptr)
        {
            return temp;
        }
        if (key < temp->data)
        {
            temp->left = deleteNode(temp->left, key);
        }
        else if (key > temp->data)
        {
            temp->right = deleteNode(temp->right, key);
        }
        else
        {
            if (temp->left == nullptr)
            {
                Node *tempRight = temp->right;
                delete temp;
                return tempRight;
            }
            else if (temp->right == nullptr)
            {
                Node *tempLeft = temp->left;
                delete temp;
                return tempLeft;
            }

            Node *successor = findMin(temp->right);
            temp->data = successor->data;

            temp->right = deleteNode(temp->right, successor->data);
        }
        return temp;
    }

    Node *findMin(Node *temp)
    {
        while (temp->left != nullptr)
        {
            temp = temp->left;
        }
        return temp;
    }

    Node *findMax(Node *temp)
    {
        while (temp->right != nullptr)
        {
            temp = temp->right;
        }
        return temp;
    }

    int printTree(Node *n, int v = 0)
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
        cout << "6. Search an element.\n";
        cout << "7. Print minimum and maximum value in the tree.\n";
        cout << "8. Delete an element.\n";
        cout << "0. Exit.\n";
        cout << "-----------------------------------------------------------\n";
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
        case 5:
            cout << "Asceding Order: " << endl;
            tree.ascending(tree.getRoot());
            cout << endl;
            break;
        case 6:
            cout << "Enter the element you want to search: ";
            int searchKey;
            cin >> searchKey;
            if (tree.search(searchKey, tree.getRoot()))
            {
                cout << "Element " << searchKey << " found in tree\n"
                     << endl;
            }
            else
            {
                cout << "Element " << searchKey << " not found in tree\n"
                     << endl;
            }
            break;
        case 7:
            cout << "The minimun value is: " << tree.findMin(tree.getRoot()) << endl;
            cout << "The maximum value is: " << tree.findMax(tree.getRoot()) << endl;
            break;
        case 8:
            cout << "Enter value to be deleted: ";
            int key;
            cin >> key;
            tree.deleteNode(tree.getRoot(), key);
            cout << key << " deleted from the tree" << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    }
    return 0;
}