#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *left, *right;
    bool lbit, rbit;

    Node()
    {
        data = 0;
        left = right = nullptr;
        lbit = rbit = false;
    } 

    Node(int val)
    {
        data = val;
        left = right = nullptr;
        lbit = rbit = false;
    }
    friend class TBST;
};

class TBST
{
    Node *root, *head;

public:
    TBST() : root(nullptr) {}

    void create()
    {
        int val;
        Node *p, *q;

        if (head == nullptr)
        {
            p = new Node();
            head = p;
            p->left = p->right = p;
            p->lbit = true;
            p->rbit = false;

            cout << "\nEnter the data for the root node:  ";
            cin >> val;

            q = new Node(val);
            linsert(head, q);
        }
        else
        {   
            cout << "\nTree head is created\n";
            cout << "\nEnter data to be Inserted: ";
            cin >> val;
            head->left = insert(head->left, val);
        }
    }

    Node *insert(Node *temp, int val)
    {
        Node* current = new Node(val);
        if(val < temp->data){
            if(temp->lbit == true){
                linsert(temp, current);
            }
            else{
                current = insert(temp->left, val);
            }
        }
        else if(val > temp->data){
            if(temp->rbit == true){
                rinsert(temp, current);
            }
            else{
                current = insert(temp->right, val);
            }
        }
        return temp;
    }

    void linsert(Node *s, Node *temp)
    {
        temp->left = s->left;
        temp->right = s;
        temp->lbit = s->lbit;
        temp->rbit = false;
        s->left = temp;
        s->lbit = true;
    }

    void rinsert(Node *s, Node *temp)
    {
        temp->right = s->right;
        temp->left = s;
        temp->rbit = s->rbit;
        temp->lbit = false;
        s->right = temp;
        s->rbit = true;
    }

    void inorder()
    {
        Node *temp = head->left;

        while (temp != head)
        {
            while (temp->lbit == false)
            {
                temp = temp->left;
            }
            cout << temp->data << " ";

            while (temp->rbit == true && temp->right != head)
            {
                temp = temp->right;
                cout << temp->data << " ";
            }

            temp = temp->right;
        }
        cout << endl;
    }

    void preorder()
    {
        Node *temp = head->left;

        while (temp != head)
        {
            cout << temp->data << " ";

            if (temp->rbit == true)
            {
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
        }
        cout << endl;
    }
};

int main()
{
    TBST tree;
    int choice;
    while (true)
    {
        cout << "-----------------------------------------------------------\n";
        cout << "1. Create a node. \n";
        cout << "2. Display Inorder Traversal.\n";
        cout << "3. Display Preorder Traversal.\n";
        cout << "0. Exit.\n";
        cout << "-----------------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            tree.create();
            break;
        case 2:
            tree.inorder();
            break;
        case 3:
            tree.preorder();
            break;
        case 0:
            cout << "Exiting program..." << endl;
            return 0;

        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    }
    return 0;
}
