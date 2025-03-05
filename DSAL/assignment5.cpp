#include <iostream>
using namespace std;
class HashNode
{
public:
    int key;
    int value;
    HashNode *next;
    HashNode(int key, int value)
    {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }
};
