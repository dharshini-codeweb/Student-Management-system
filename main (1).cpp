#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    string course;

    void input() {
        cout << "Enter Student ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nAge: " << age;
        cout << "\nCourse: " << course << endl;
    }
};

void addStudent() {
    Student s;
    ofstream file("students.txt", ios::app);

    s.input();

    file << s.id << "|"
         << s.name << "|"
         << s.age << "|"
         << s.course << endl;

    file.close();

    cout << "\nStudent Added Successfully!\n";
}

void displayStudents() {
    ifstream file("students.txt");

    string line;

    cout << "\n===== Student Records =====\n";

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void searchStudent() {
    ifstream file("students.txt");

    int searchId;
    string line;

    cout << "Enter Student ID to Search: ";
    cin >> searchId;

    bool found = false;

    while (getline(file, line)) {
        int pos1 = line.find("|");
        int id = stoi(line.substr(0, pos1));

        if (id == searchId) {
            cout << "\nRecord Found:\n";
            cout << line << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent Not Found!\n";
    }

    file.close();
}

void deleteStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    int deleteId;
    string line;

    cout << "Enter Student ID to Delete: ";
    cin >> deleteId;

    bool found = false;

    while (getline(file, line)) {
        int pos1 = line.find("|");
        int id = stoi(line.substr(0, pos1));

        if (id != deleteId) {
            temp << line << endl;
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

void updateStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");

    int updateId;
    string line;

    cout << "Enter Student ID to Update: ";
    cin >> updateId;

    bool found = false;

    while (getline(file, line)) {
        int pos1 = line.find("|");
        int id = stoi(line.substr(0, pos1));

        if (id == updateId) {
            Student s;

            cout << "\nEnter New Details:\n";
            s.input();

            temp << s.id << "|"
                 << s.name << "|"
                 << s.age << "|"
                 << s.course << endl;

            found = true;
        } else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent Updated Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            cout << "\nExiting Program...\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}