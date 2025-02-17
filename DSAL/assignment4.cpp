#include <iostream>
#include <string>
using namespace std;

#define SIZE 10

class DataItem
{
public:
    string phoneNumber;
    int key;

    DataItem() : phoneNumber(""), key(-1) {}
    DataItem(string num, int k) : phoneNumber(num), key(k) {}
};

class HashTable
{
private:
    DataItem *hashArray[SIZE];
    DataItem *dummyItem;

public:
    HashTable()
    {
        dummyItem = new DataItem("-1", -1);
        for (int i = 0; i < SIZE; i++)
        {
            hashArray[i] = nullptr;
        }
    }

    int hashCode(int key)
    {
        return key % SIZE;
    }

    void insertWithReplacement(int key, string phoneNumber)
    {
        DataItem *item = new DataItem(phoneNumber, key);
        int hashIndex = hashCode(key);

        while (hashArray[hashIndex] != nullptr && hashArray[hashIndex]->key != -1)
        {
            hashIndex++;
            hashIndex %= SIZE;
        }

        hashArray[hashIndex] = item;
    }

    void insertWithoutReplacement(int key, string phoneNumber)
    {
        DataItem *item = new DataItem(phoneNumber, key);
        int hashIndex = hashCode(key);

        while (hashArray[hashIndex] != nullptr && hashArray[hashIndex]->key != -1)
        {
            hashIndex++;
            hashIndex %= SIZE;
        }

        if (hashArray[hashIndex] == nullptr)
        {
            hashArray[hashIndex] = item;
        }
    }

    DataItem *deleteItem(int key)
    {
        int hashIndex = hashCode(key);

        while (hashArray[hashIndex] != nullptr)
        {
            if (hashArray[hashIndex]->key == key)
            {
                DataItem *temp = hashArray[hashIndex];
                hashArray[hashIndex] = dummyItem;
                return temp;
            }

            hashIndex++;
            hashIndex %= SIZE;
        }

        return nullptr;
    }

    DataItem *searchWithReplacement(int key, int &comparisons)
    {
        int hashIndex = hashCode(key);
        comparisons = 0;

        while (hashArray[hashIndex] != nullptr)
        {
            comparisons++;

            if (hashArray[hashIndex]->key == key)
                return hashArray[hashIndex];

            hashIndex++;
            hashIndex %= SIZE;
        }

        return nullptr;
    }

    DataItem *searchWithoutReplacement(int key, int &comparisons)
    {
        int hashIndex = hashCode(key);
        comparisons = 0;

        while (hashArray[hashIndex] != nullptr)
        {
            comparisons++;

            if (hashArray[hashIndex]->key == key)
                return hashArray[hashIndex];

            hashIndex++;
            hashIndex %= SIZE;
        }

        return nullptr;
    }

    void printTable()
    {
        for (int i = 0; i < SIZE; ++i)
        {
            if (hashArray[i] != nullptr && hashArray[i]->key != -1)
            {
                cout << "\033[42m Index " << i << ":\033[44m Key = " << hashArray[i]->key
                     << ", \033[44m Phone Number = " << hashArray[i]->phoneNumber <<"\033[0m"<< endl;
            }
            else
            {
                cout << "\033[42m Index " << i << ": Empty \033[0m" << endl;
            }
        }
    }
};

int main()
{
    HashTable ht;
    int choice;

    while (true)
    {
        cout << "-----------------------------------------------------------\n";
        cout << "1. Insert a number with replacement. \n";
        cout << "2. Insert a number without replacement. \n";
        cout << "3. View Telephone book.\n";
        cout << "4. Search a number with replacement.\n";
        cout << "5. Search a number without replacement.\n";
        cout << "6. Delete a number\n";
        cout << "0. Exit.\n";
        cout << "-----------------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            {
                string phoneNumber;
                int key;
                cout << "Enter the Phone Number (10 digits): ";
                cin >> phoneNumber;
                key = phoneNumber[9] - '0';
                ht.insertWithReplacement(key, phoneNumber);
            }
            break;

        case 2:
            {
                string phoneNumber;
                int key;
                cout << "Enter the Phone Number (10 digits): ";
                cin >> phoneNumber;
                key = phoneNumber[9] - '0';
                ht.insertWithoutReplacement(key, phoneNumber);
            }
            break;

        case 3:
            ht.printTable();
            break;

        case 4:
            {
                string phoneNumber;
                int s_key, comparisons = 0;
                cout << "Enter the Phone Number to be searched: ";
                cin >> phoneNumber;
                s_key = phoneNumber[9] - '0';
                DataItem* result = ht.searchWithReplacement(s_key, comparisons);
                if (result != nullptr)
                {
                    cout << "Found item: Key = " << result->key << ", Phone Number = " << result->phoneNumber << endl;
                    cout << "Comparisons: " << comparisons << endl;
                }
                else
                {
                    cout << "Phone number not found!" << endl;
                }
            }
            break;

        case 5:
            {
                string phoneNumber;
                int s_key, comparisons = 0;
                cout << "Enter the Phone Number to be searched: ";
                cin >> phoneNumber;
                s_key = phoneNumber[9] - '0';
                DataItem* result = ht.searchWithoutReplacement(s_key, comparisons);
                if (result != nullptr)
                {
                    cout << "Found item: Key = " << result->key << ", Phone Number = " << result->phoneNumber << endl;
                    cout << "Comparisons: " << comparisons << endl;
                }
                else
                {
                    cout << "Phone number not found!" << endl;
                }
            }
            break;

        case 6:
            {
                string phoneNumber;
                int del_key;
                cout << "Enter the Phone Number to be deleted: ";
                cin >> phoneNumber;
                del_key = phoneNumber[9] - '0';
                DataItem* deletedItem = ht.deleteItem(del_key);
                if (deletedItem != nullptr)
                {
                    cout << "Deleted item: Key = " << deletedItem->key << ", Phone Number = " << deletedItem->phoneNumber << endl;
                    delete deletedItem;
                }
                else
                {
                    cout << "Phone number not found for deletion!" << endl;
                }
            }
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
