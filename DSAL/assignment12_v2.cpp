#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Student
{
    int rollNo;
    char name[20];
    char division;
    char address[30];
};

const char *FILENAME = "students.dat";

void insertStudent()
{
    Student s;
    cout << "Enter Roll No: ";
    cin >> s.rollNo;
    cout << "Enter Name: ";
    cin >> s.name;
    cout << "Enter Division: ";
    cin >> s.division;
    cout << "Enter Address: ";
    cin >> s.address;

    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    if (!file)
    {
        // If file doesn't exist, create it
        file.open(FILENAME, ios::out | ios::binary);
        file.close();
        file.open(FILENAME, ios::in | ios::out | ios::binary);
    }

    int pos = (s.rollNo - 1) * sizeof(Student);
    file.seekp(pos, ios::beg);
    file.write((char *)&s, sizeof(Student));
    file.close();

    cout << "Student record inserted successfully.\n";
}

void deleteStudent()
{
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;

    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    if (!file)
    {
        cout << "File not found.\n";
        return;
    }

    int pos = (roll - 1) * sizeof(Student);
    file.seekg(pos, ios::beg);
    Student s;
    file.read((char *)&s, sizeof(Student));

    if (s.rollNo != roll)
    {
        cout << "Record not found.\n";
        file.close();
        return;
    }

    s.rollNo = -1;      // logical deletion
    strcpy(s.name, ""); // optional: clear data
    s.division = ' ';
    strcpy(s.address, "");

    file.seekp(pos, ios::beg);
    file.write((char *)&s, sizeof(Student));
    file.close();

    cout << "Student record deleted (logically).\n";
}

void displayStudent()
{
    int roll;
    cout << "Enter Roll No to display: ";
    cin >> roll;

    ifstream file(FILENAME, ios::in | ios::binary);
    if (!file)
    {
        cout << "File not found.\n";
        return;
    }

    int pos = (roll - 1) * sizeof(Student);
    file.seekg(pos, ios::beg);
    Student s;
    file.read((char *)&s, sizeof(Student));

    if (s.rollNo == -1 || s.rollNo != roll)
    {
        cout << "Student record not found.\n";
    }
    else
    {
        cout << "\n--- Student Details ---\n";
        cout << "Roll No: " << s.rollNo << "\nName: " << s.name
             << "\nDivision: " << s.division << "\nAddress: " << s.address << endl;
    }

    file.close();
}

int main()
{
    int choice;

    do
    {
        cout << "\n--- Direct Access Student System ---\n";
        cout << "1. Insert Student\n2. Delete Student\n3. Display Student\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            insertStudent();
            break;
        case 2:
            deleteStudent();
            break;
        case 3:
            displayStudent();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
