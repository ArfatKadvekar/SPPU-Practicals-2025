#include <iostream>
using namespace std;

class HashNode {
public:
    int key;
    int value;
    HashNode* next;

    HashNode(int key, int value) {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }
};

class HashTable {
private:
    HashNode** htable;
    int tableSize;

    int HashFunc(int key) {
        return key % tableSize;
    }

public:
    HashTable(int size = 10) {
        tableSize = size;
        htable = new HashNode*[tableSize];

        for (int i = 0; i < tableSize; i++) {
            htable[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < tableSize; i++) {
            HashNode* entry = htable[i];
            while (entry != nullptr) {
                HashNode* prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
        delete[] htable;
    }

    void Insert(int key, int value) {
        int hash_val = HashFunc(key);
        HashNode* entry = htable[hash_val];

        while (entry != nullptr) {
            if (entry->key == key) {
                entry->value = value;
                return;
            }
            entry = entry->next;
        }

        HashNode* newNode = new HashNode(key, value);
        newNode->next = htable[hash_val];
        htable[hash_val] = newNode;
    }

    void Delete(int key) {
        int hash_val = HashFunc(key);
        HashNode* entry = htable[hash_val];
        HashNode* prev = nullptr;

        while (entry != nullptr && entry->key != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr) {
            cout << "No element found at key " << key << endl;
            return;
        }

        if (prev == nullptr) {
            htable[hash_val] = entry->next;
        } else {
            prev->next = entry->next;
        }
        delete entry;
        cout << "Element Deleted" << endl;
    }

    int Find(int key) {
        int hash_val = HashFunc(key);
        HashNode* entry = htable[hash_val];

        while (entry != nullptr) {
            if (entry->key == key) {
                cout << "Entry found, Value: " << entry->value << endl;
                return entry->value;
            }
            entry = entry->next;
        }

        cout << "No element found at key " << key << endl;
        return -1;
    }

    void Display() {
        cout << "------------------------------------------------------------" << endl;
        cout << "Displaying HashTable contents:" << endl;
        for (int i = 0; i < tableSize; i++) {
            cout << "Index " << i << ": ";
            HashNode* entry = htable[i];
            while (entry != nullptr) {
                cout << "(" << entry->key << ", " << entry->value << ") -> ";
                entry = entry->next;
            }
            cout << "NULL" << endl;
        }
        cout << "------------------------------------------------------------" << endl;
    }
};

int main() {
    HashTable ht;
    int choice;
    while (true) {
        cout << "-----------------------------------------------------------\n";
        cout << "1. Insert a Word. \n";
        cout << "2. Find a Word. \n";
        cout << "3. Delete a Word.\n";
        cout << "4. View Table.\n";
        cout << "0. Exit.\n";
        cout << "-----------------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the key: ";
            int key, val;
            cin >> key;
            cout << "Enter the value: ";
            cin >> val;
            ht.Insert(key, val);
            break;

        case 2:
            cout << "Enter the key: ";
            int fkey;
            cin >> fkey;
            ht.Find(fkey);
            break;

        case 3:
            cout << "Enter the key: ";
            int dkey;
            cin >> dkey;
            ht.Delete(dkey);
            break;

        case 4:
            ht.Display();
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
