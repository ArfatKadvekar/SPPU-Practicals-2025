#include <iostream>
#include<stack>
#include<queue>
#include "stack.cpp"
using namespace std;
class Node
{
public: //fix this
    int data;
    Node *left;
    Node *right;

public:
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
    friend class BinaryTree;
};

class BinaryTree
{
    Node *root;
    Stack<Node *> st;

public:
    BinaryTree() : root(nullptr) {}

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
        else
        {
            cout << "Enter where you want to insert the node " << temp->data << " [L/R]: ";
            char loc;
            cin >> loc;
            if (loc == 'l' || loc == 'L')
            {
                temp->left = insert(temp->left, val);
            }
            else
            {
                temp->right = insert(temp->right, val);
            }
        }
        return temp;
    }
    void inOrder(Node* temp){
        if(temp == nullptr)
        return;
        stack<Node*> st;
        while (!st.empty() || temp!=nullptr)
        {
            if(temp != nullptr){
                st.push(temp);
                temp = temp->left;
            }
            else{
                temp = st.top();
                st.pop();
                cout << temp->data << " ";
                temp = temp->right;
            }
        }
    }

    void preOrder(Node* temp){
        if(temp == nullptr)
        return;
        stack<Node*>st;
        while (!st.empty() || temp!=nullptr)
        {
            if(temp!=nullptr){
                cout << temp->data << " ";
                st.push(temp);
                temp = temp->left;
            }
            else{
                temp = st.top();
                st.pop();
                temp = temp->right;
            }
        }
    }

    void postOrder(Node* temp){
        if(temp == nullptr)
        return;
        stack<Node*> st1, st2;
        st1.push(temp);
        while (!st1.empty())
        {
            temp = st1.top();
            st1.pop();
            st2.push(temp); 
            if(temp->left != nullptr){
                st1.push(temp->left);
            }
            if(temp->right != nullptr){
                st1.push(temp->right);
            }
        }
        while (!st2.empty())
        {
            cout << st2.top()->data << " ";
            st2.pop();
        }  
    }

    int height(Node* root) {
        if (root == nullptr) return 0;
        queue<Node*> q;
        q.push(root);
        int height = 0;
        while (!q.empty()) {
            int nodeCount = q.size();
            height++;
            while (nodeCount--) {
                Node* current = q.front();
                q.pop();
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
        }
        return height;
    }


    int countNodes(Node* root) {
        if (root == nullptr) return 0;
        int count = 0;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            count++;
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        return count;
    }


    void countLeavesAndInternalNodes(Node* root) {
        if (root == nullptr) return;
        int leaves = 0, internalNodes = 0;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            if (current->left == nullptr && current->right == nullptr) {
                leaves++;
            } else {
                internalNodes++;
            }
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        cout << "Leaves: " << leaves << ", Internal Nodes: " << internalNodes << endl;
    }


    void swapChildren(Node* root) {
        if (root == nullptr) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            swap(current->left, current->right);
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }


    Node* copyTree(Node* root) {
        if (root == nullptr) return nullptr;
        queue<Node*> q;
        queue<Node*> newQ;
        Node* newRoot = new Node(root->data);
        q.push(root);
        newQ.push(newRoot);
        while (!q.empty()) {
            Node* current = q.front();
            Node* newCurrent = newQ.front();
            q.pop();
            newQ.pop();
            if (current->left) {
                newCurrent->left = new Node(current->left->data);
                q.push(current->left);
                newQ.push(newCurrent->left);
            }
            if (current->right) {
                newCurrent->right = new Node(current->right->data);
                q.push(current->right);
                newQ.push(newCurrent->right);
            }
        }
        return newRoot;
    }


    void deleteAllNodes(Node* root) {
        if (root == nullptr) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            delete current;
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        root = nullptr;
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

    Node* getRoot() {
        return root;
    }
    int getData(){
        return root->data;
    }
};

int main()
{
    BinaryTree tree;
    int choice;
    while (true) {
        cout << "-----------------------------------------------------------\n";
        cout << "1. Create a node. \n";
        cout << "2. Print In-Order traversal.\n";
        cout << "3. Print Pre-Order traversal.\n";
        cout << "4. Print Post-Order traversal.\n";
        cout << "5. Print all three traversals.\n";
        cout << "6. Height of the tree.\n";
        cout << "7. Count total nodes.\n";
        cout << "8. Count number of leaves and internal nodes.\n";
        cout << "9. Swap the left and right children.\n";
        cout << "10. Copy the tree.\n";
        cout << "11. Delete all nodes in the tree.\n";
        cout << "12. Display tree.\n";
        cout << "0. Exit.\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the data: ";
            int d;
            cin >> d;
            tree.create(d);
            break;
        case 2:
            cout << "In-Order Traversal of the tree: ";
            tree.inOrder(tree.getRoot());
            cout << endl;
            break;
        case 3:
            cout << "Pre-Order Traversal of the tree: ";
            tree.preOrder(tree.getRoot());
            cout << endl;
            break;
        case 4:
            cout << "Post-Order Traversal of the tree: ";
            tree.postOrder(tree.getRoot());
            cout << endl;
            break;
        case 5:
            cout << "In-Order: ";
            tree.inOrder(tree.getRoot());
            cout << "\nPre-Order: ";
            tree.preOrder(tree.getRoot());
            cout << "\nPost-Order: ";
            tree.postOrder(tree.getRoot());
            cout << endl;
            break;
        case 6:
            cout << "Height of the tree: " << tree.height(tree.getRoot()) << endl;
            break;
        case 7:
            cout << "Total nodes: " << tree.countNodes(tree.getRoot()) << endl;
            break;
        case 8:
            tree.countLeavesAndInternalNodes(tree.getRoot());
            break;
        case 9:
            tree.swapChildren(tree.getRoot());
            cout << "Left and Right children swapped." << endl;
            break;
        case 10:
            {
                Node* copiedTree = tree.copyTree(tree.getRoot());
                cout << "Tree copied." << endl;
                BinaryTree copiedBinaryTree;
                copiedBinaryTree.create(copiedTree->data);
                copiedBinaryTree.printTree(copiedBinaryTree.getRoot());
            }
            break;
        case 11:
            tree.deleteAllNodes(tree.getRoot());
            cout << "All nodes deleted." << endl;
            break;
        case 12:
            tree.printTree(tree.getRoot());
            break;
        case 0:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}