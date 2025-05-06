#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
    int rollno;
    char name[30];
    char division;
    char address[50];

public:
    void accept() {
        cout << "\nEnter Roll Number: ";
        cin >> rollno;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Division: ";
        cin >> division;
        cout << "Enter Address: ";
        cin.ignore(); // flush newline
        cin.getline(address, 50);
    }

    void display() {
        cout << "\nRoll No: " << rollno
             << "\nName: " << name
             << "\nDivision: " << division
             << "\nAddress: " << address << "\n";
    }

    int getRollNo() {
        return rollno;
    }
};

void addStudent() {
    Student s;
    ofstream fout("student.txt", ios::app | ios::binary);
    s.accept();
    fout.write((char*)&s, sizeof(s));
    fout.close();
    cout << "\nStudent record added successfully!";
}

void displayStudent(int rollno) {
    Student s;
    ifstream fin("student.txt", ios::binary);
    bool found = false;

    while (fin.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == rollno) {
            s.display();
            found = true;
            break;
        }
    }

    fin.close();

    if (!found) {
        cout << "\nStudent record not found!";
    }
}

void deleteStudent(int rollno) {
    Student s;
    ifstream fin("student.txt", ios::binary);
    ofstream fout("temp.txt", ios::binary);
    bool found = false;

    while (fin.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == rollno) {
            found = true;
            continue; // skip writing to delete
        }
        fout.write((char*)&s, sizeof(s));
    }

    fin.close();
    fout.close();

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (found) {
        cout << "\nStudent record deleted successfully!";
    } else {
        cout << "\nStudent record not found!";
    }
}

int main() {
    int choice, rollno;

    do {
        cout << "\n\n==== Student Record System ====";
        cout << "\n1. Add Student";
        cout << "\n2. Display Student by Roll No";
        cout << "\n3. Delete Student by Roll No";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "\nEnter Roll Number to Display: ";
                cin >> rollno;
                displayStudent(rollno);
                break;
            case 3:
                cout << "\nEnter Roll Number to Delete: ";
                cin >> rollno;
                deleteStudent(rollno);
                break;
            case 4:
                cout << "\nExiting program...";
                break;
            default:
                cout << "\nInvalid choice!";
        }
    } while (choice != 4);

    return 0;
}
