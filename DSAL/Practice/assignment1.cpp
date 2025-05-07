#include<iostream>
#include<stack>
using namespace std;

class Node {
    int data;
    Node *left, *right;
public:
    Node(int val){
        data = val;
        left = nullptr;
        right = nullptr;
    }
    friend class BinaryTree;
};

class BinaryTree{
public:
    Node* root;
    BinaryTree(){
        root = NULL;
    }

    void create (int val){
        if (root == nullptr){
            root = new Node(val);
        }
        else{
            root = insert(root, val);
        }
    }

    Node* insert(Node* temp, int val){
        if (temp==nullptr){
            Node* newNode = new Node(val);
            return newNode;
        }
        else{
            cout << "Enter where you want to insert the node " << temp->data << " [L/R]: ";
            char loc;
            cin >> loc;
            if(loc == 'l' || loc=='L'){
                temp->left = insert(temp->left, val);
            }
            else{
                temp->right = insert(temp->right, val);
            }
        }
        return temp;
    }

    void inorder(Node* temp){
        if(temp == nullptr)
        return;
        else{
            inorder(temp->left);
            cout << temp->data << " ";
            inorder(temp->right);
        }
    }
    void preorder(Node* temp){
        if(temp == nullptr)
        return;
        else{
            cout << temp->data << " ";
            preorder(temp->left);
            preorder(temp->right);
        }
    }
    void postorder(Node* temp){
        if(temp == nullptr)
        return;
        else{
            
            postorder(temp->left);
            postorder(temp->right);
            cout << temp->data << " ";
        }
    }
    void iinorder(Node* temp){
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

    void ipreorder(Node* temp){
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

    void ipostorder(Node* temp){
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
};

int main(){
    BinaryTree b1;
    int choice;
    while(true){
        cout << "-----------------------------------------------------------\n";

        cout << "1. Create a node. \n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter the Data: ";
            int d;
            cin >> d;
            b1.create(d);
            break;
        default:
            break;
        }
        b1.inorder(b1.root);
        cout << endl;
        b1.iinorder(b1.root);
        cout << endl;
        b1.ipreorder(b1.root);
        cout << endl;
        b1.preorder(b1.root);
        cout << endl;
        b1.postorder(b1.root);
        cout << endl;
        b1.postorder(b1.root);
    }
    return 0;
}