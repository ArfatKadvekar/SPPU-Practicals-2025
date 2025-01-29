#include<iostream>
#include<string>
#include<cstring>
using namespace std;

class Node{
    string data;
    Node* left;
    Node* right;
public:    
    Node(string val) : data(val), left(nullptr), right(nullptr) {}
    friend class ExpressionTree;
};

class ExpressionTree{
    Node* root;
public:
    ExpressionTree(){
        root = nullptr;
    }

    void readString(string s){
        
    }
};