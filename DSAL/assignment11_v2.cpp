#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int roll, div;
    string name, address;

    void getData() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter roll no: ";
        cin >> roll;
        cout << "Enter division: ";
        cin >> div;
        cout << "Enter address: ";
        cin >> address;
    }

    void display() {
        cout << "Name: " << name << ", Roll: " << roll << ", Div: " << div << ", Address: " << address << endl;
    }
};

class MyFile {
    string filename;
public:
    MyFile() {
        cout << "Enter filename (with .txt): ";
        cin >> filename;
        ofstream clear(filename);
        clear.close();
    }

    void addRecord() {
        ofstream file(filename, ios::app);
        Student s;
        s.getData();
        file << s.roll << " " << s.name << " " << s.div << " " << s.address << endl;
        file.close();
    }

    void displayAll() {
        ifstream file(filename);
        Student s;
        bool found = false;
        while (file >> s.roll >> s.name >> s.div >> s.address) {
            s.display();
            found = true;
        }
        if (!found)
            cout << "No records found." << endl;
        file.close();
    }

    void displayStudent(int r) {
        ifstream file(filename);
        Student s;
        bool found = false;
        while (file >> s.roll >> s.name >> s.div >> s.address) {
            if (s.roll == r) {
                s.display();
                found = true;
                break;
            }
        }
        if (!found)
            cout << "Student with roll " << r << " not found." << endl;
        file.close();
    }

    void deleteRecord(int r) {
        ifstream file(filename);
        ofstream temp("temp.txt");
        Student s;
        bool found = false;

        while (file >> s.roll >> s.name >> s.div >> s.address) {
            if (s.roll == r) {
                cout << "Deleting: ";
                s.display();
                found = true;
            } else {
                temp << s.roll << " " << s.name << " " << s.div << " " << s.address << endl;
            }
        }

        file.close();
        temp.close();
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());

        if (!found)
            cout << "Student with roll " << r << " not found." << endl;
    }
};

int main() {
    MyFile file;
    int choice, roll;

    do {
        cout << "\n1. Add Student\n2. Display All\n3. Display Specific Student\n4. Delete Student\n5. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: file.addRecord(); break;
            case 2: file.displayAll(); break;
            case 3:
                cout << "Enter roll number: ";
                cin >> roll;
                file.displayStudent(roll);
                break;
            case 4:
                cout << "Enter roll number to delete: ";
                cin >> roll;
                file.deleteRecord(roll);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
