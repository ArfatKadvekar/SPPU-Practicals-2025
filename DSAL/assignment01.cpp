#include<iostream> 
using namespace std;

class Node
{
    int data;
    Node* left;
    Node* right;
public:
    Node(int val): data(val), left(nullptr), right(nullptr){}
    friend class BinaryTree;
};

class BinaryTree{
    Node* root;
public:
    BinaryTree(): root(nullptr) {}


    void create(int val){
        if (root == nullptr){
            root = new Node(val);
        }
        else{
            insert(root, val);
        }
    }
    Node* insert(Node* temp, int val){
        if(temp == nullptr){
            Node* newNode = new Node(val);
            return newNode;
        }
        else{
            cout << "Enter where you want to insert the node " << temp->data << " [L/R]: ";
            char loc;
            cin >> loc;
            if(loc == 'l' || loc == 'L'){
                temp->left = insert(temp->left, val);
            }
            else{
                temp->right = insert(temp->right, val);
            }
        }
        return temp;
    }

    void inOrderTraversal(Node* temp) {
        if (temp == nullptr)
            return;
        inOrderTraversal(temp->left);
        cout << temp->data << " ";
        inOrderTraversal(temp->right);
    }

    void preOrderTraversal(Node* temp) {
        if (temp == nullptr)
            return;
        cout << temp->data << " ";
        preOrderTraversal(temp->left);
        preOrderTraversal(temp->right);
    }

    void postOrderTraversal(Node* temp) {
        if (temp == nullptr)
            return;
        postOrderTraversal(temp->left);
        postOrderTraversal(temp->right);
        cout << temp->data << " ";
    }
    void printIn(){
        cout << "In-Order Traversal of the tree: ";
        inOrderTraversal(root);
        cout << endl; 
    }

    void printPre(){
        cout << "Pre-Order Traversal of the tree: ";
        preOrderTraversal(root);
        cout << endl;  
    }

    void printPost(){
        cout << "Post-Order Traversal of the tree: ";
        postOrderTraversal(root);
        cout << endl; 
    }

    void printThree() {
        cout << "In-Order Traversal of the tree: ";
        inOrderTraversal(root);
        cout << endl; 

        cout << "Pre-Order Traversal of the tree: ";
        preOrderTraversal(root);
        cout << endl; 

        cout << "Post-Order Traversal of the tree: ";
        postOrderTraversal(root);
        cout << endl;  
    }

    void swapRoles(Node* temp){
        if (temp == nullptr) return;
        swap(temp->left, temp->right);
        swapRoles(temp->left);
        swapRoles(temp->right);
    }


    int height(){
        return height(root); 
    }

    int height(Node* temp){
        if (temp == nullptr) return 0;
        int leftHeight = height(temp->left);
        int rightHeight = height(temp->right);
        return max(leftHeight, rightHeight) + 1;
    }
    
    int countTotalNodes(Node* temp, int &count){
        if (temp == nullptr) return 0;
        count++;
        countTotalNodes(temp->left, count);
        countTotalNodes(temp->right, count);
        return count;
    }

    int printTotalNodes(){
        int count = 0;
        return countTotalNodes(root, count);
    }

    int countLeaves(Node* temp) {
        if (temp == nullptr) return 0;
        if (temp->left == nullptr && temp->right == nullptr) return 1;
        return countLeaves(temp->left) + countLeaves(temp->right);
    }

    int countInternalNodes(Node* temp) {
        if (temp == nullptr || (temp->left == nullptr && temp->right == nullptr)) return 0;
        return 1 + countInternalNodes(temp->left) + countInternalNodes(temp->right);
    }

   	void eraseTree(Node *temp){
		if(temp==NULL)
			return;
		eraseTree(temp->left);
		eraseTree(temp->right);
		delete temp;
	}
    void operator=(BinaryTree b1){
		this->root=b1.copyTree(b1.root);
	}

	Node* copyTree(Node *p)
{
    if (p == NULL)
    {
        return NULL;
    }
    else
    {
        Node *temp = new Node(p->data);
        temp->left = copyTree(p->left);
        temp->right = copyTree(p->right);
        return temp;
    }
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
};

int main() {
    BinaryTree tree;
    int choice;
    while (true) {  
        cout << "-----------------------------------------------------------\n";
        cout << "1. Create a node. \n";
        cout << "2. Print in In-Order traversal. \n";
        cout << "3. Print in Pre-Order traversal.\n";
        cout << "4. Print in Post-Order traversal.\n";
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
            tree.printIn();
            break;
        case 3:
            tree.printPre();
            break;
        case 4:
            tree.printPost();
            break;
        case 5:
            tree.printThree();
            break;
        case 6:
            cout << "Height of the tree is: " << tree.height() << endl;
            break;
        case 7:
            cout << "Total nodes in the tree: " << tree.printTotalNodes() << endl;
            break;
        case 8:
            cout << "Number of leaves: " << tree.countLeaves(tree.getRoot()) << endl;
            cout << "Number of internal nodes: " << tree.countInternalNodes(tree.getRoot()) << endl;
            break;
        case 9:
            tree.swapRoles(tree.getRoot());
            cout << "Left and right children swapped." << endl;
            break;
        case 10:
        {
            BinaryTree copiedTree;
            copiedTree = tree;
            cout << "Tree copied successfully." << endl;
            
        }
        break;
            
        case 11:
            tree.eraseTree(tree.getRoot());
            cout << "All nodes have been deleted." << endl;
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
