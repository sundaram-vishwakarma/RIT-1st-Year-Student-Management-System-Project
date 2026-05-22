#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Student {
    int id;
    string name;
    float marks;
};

// Safe integer input
int getValidInt() {
    string input;
    int value;
    char extra;

    while (true) {
        getline(cin, input);
        stringstream ss(input);

        if (ss >> value && !(ss >> extra)) {
            return value;
        } else {
            cout << "Invalid input! Enter a valid integer: ";
        }
    }
}

// Safe float input
float getValidFloat() {
    string input;
    float value;
    char extra;

    while (true) {
        getline(cin, input);
        stringstream ss(input);

        if (ss >> value && !(ss >> extra)) {
            return value;
        } else {
            cout << "Invalid input! Enter valid marks: ";
        }
    }
}

// Add student
void addStudent() {
    ifstream fin("students.txt");
    string line;
    int newId, found = 0;

    cout << "Enter ID: ";
    newId = getValidInt();

    // Check duplicate ID
    while (getline(fin, line)) {
        stringstream ss(line);
        string temp;

        getline(ss, temp, ',');
        if (stoi(temp) == newId) {
            found = 1;
            break;
        }
    }
    fin.close();

    if (found) {
        cout << "ID already exists!\n";
        return;
    }

    ofstream fout("students.txt", ios::app);

    Student s;
    s.id = newId;

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Marks: ";
    s.marks = getValidFloat();

    fout << s.id << "," << s.name << "," << s.marks << endl;

    fout.close();

    cout << "Student added successfully!\n";
}

// Display students
void displayStudents() {
    ifstream fin("students.txt");
    string line;

    if (!fin) {
        cout << "No records found!\n";
        return;
    }

    cout << "\n--- Student Records ---\n";

    while (getline(fin, line)) {
        stringstream ss(line);
        string id, name, marks;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, marks);

        cout << "ID: " << id << " | Name: " << name << " | Marks: " << marks << endl;
    }

    fin.close();
}

// Search student
void searchStudent() {
    ifstream fin("students.txt");
    string line;
    int id, found = 0;

    if (!fin) {
        cout << "No records found!\n";
        return;
    }

    cout << "Enter ID to search: ";
    id = getValidInt();

    while (getline(fin, line)) {
        stringstream ss(line);
        string tempId, name, marks;

        getline(ss, tempId, ',');
        getline(ss, name, ',');
        getline(ss, marks);

        if (stoi(tempId) == id) {
            cout << "Found: " << name << " (Marks: " << marks << ")\n";
            found = 1;
            break;
        }
    }

    if (!found)
        cout << "Student not found!\n";

    fin.close();
}

// Delete student
void deleteStudent() {
    ifstream fin("students.txt");
    ofstream temp("temp.txt");
    string line;
    int id, found = 0;

    if (!fin) {
        cout << "No records found!\n";
        return;
    }

    cout << "Enter ID to delete: ";
    id = getValidInt();

    while (getline(fin, line)) {
        stringstream ss(line);
        string tempId;

        getline(ss, tempId, ',');

        if (stoi(tempId) != id) {
            temp << line << endl;
        } else {
            found = 1;
        }
    }

    fin.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Record deleted successfully!\n";
    else
        cout << "Student not found!\n";
}

// Update student
void updateStudent() {
    ifstream fin("students.txt");
    ofstream temp("temp.txt");
    string line;
    int id, found = 0;

    if (!fin) {
        cout << "No records found!\n";
        return;
    }

    cout << "Enter ID to update: ";
    id = getValidInt();

    while (getline(fin, line)) {
        stringstream ss(line);
        string tempId, name, marks;

        getline(ss, tempId, ',');
        getline(ss, name, ',');
        getline(ss, marks);

        if (stoi(tempId) == id) {
            cout << "Enter new name: ";
            getline(cin, name);

            cout << "Enter new marks: ";
            float newMarks = getValidFloat();

            stringstream ms;
            ms << newMarks;
            marks = ms.str();

            found = 1;
        }

        temp << tempId << "," << name << "," << marks << endl;
    }

    fin.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Record updated successfully!\n";
    else
        cout << "Student not found!\n";
}

// Main menu
int main() {
    int choice;

    do {
        cout << "\n--- Student Record Manager ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";

        choice = getValidInt();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
