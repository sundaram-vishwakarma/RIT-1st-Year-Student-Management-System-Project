#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    float marks;
};

// Safe integer input
int getValidInt() {
    char input[100];
    int value;
    char extra;

    while (1) {
        fgets(input, sizeof(input), stdin);

        /*
        sscanf(input, "%d %c", &value, &extra)
            Reads data from the string input
            %d → reads an integer into value
            %c → reads the next character into extra
            Return value = number of successful reads

            Examples:

            Input	Return
            "123"	1
            "123a"	2
            "abc"	0
        */

        if (sscanf(input, "%d %c", &value, &extra) == 1) {
            return value;
        } else {
            printf("Invalid input! Please enter a valid integer: ");
        }
    }
}

// Safe float input
float getValidFloat() {
    char input[100];
    float value;
    char extra;

    while (1) {
        fgets(input, sizeof(input), stdin);

        if (sscanf(input, "%f %c", &value, &extra) == 1) {
            return value;
        } else {
            printf("Invalid input! Enter valid marks: ");
        }
    }
}

// Safe string input
void getValidString(char *str, int size) {
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0'; // remove newline
}

// Add student
void addStudent() {
    FILE *fp = fopen("students.txt", "r");
    struct Student s;
    int newId, found = 0;

    printf("Enter ID: ");
    newId = getValidInt();

    // Check duplicate ID
    if (fp != NULL) {
        while (fscanf(fp, "%d,%49[^,],%f\n", &s.id, s.name, &s.marks) == 3) {
            if (s.id == newId) {
                found = 1;
                break;
            }
        }
        fclose(fp);
    }

    if (found) {
        printf("ID already exists! Try a different ID.\n");
        return;
    }

    FILE *fp_append = fopen("students.txt", "a");

    s.id = newId;

    printf("Enter Name: ");
    getValidString(s.name, sizeof(s.name));

    printf("Enter Marks: ");
    s.marks = getValidFloat();

    fprintf(fp_append, "%d,%s,%.2f\n", s.id, s.name, s.marks);

    fclose(fp_append);

    printf("Student added successfully!\n");
}

// Display students
void displayStudents() {
    FILE *fp = fopen("students.txt", "r");
    struct Student s;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fscanf(fp, "%d,%49[^,],%f\n", &s.id, s.name, &s.marks) == 3) {
        printf("ID: %d | Name: %s | Marks: %.2f\n", s.id, s.name, s.marks);
    }

    fclose(fp);
}

// Search student
void searchStudent() {
    FILE *fp = fopen("students.txt", "r");
    struct Student s;
    int id, found = 0;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter ID to search: ");
    id = getValidInt();

    while (fscanf(fp, "%d,%49[^,],%f\n", &s.id, s.name, &s.marks) == 3) {
        if (s.id == id) {
            printf("Found: %s (Marks: %.2f)\n", s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found!\n");

    fclose(fp);
}

// Delete student
void deleteStudent() {
    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Student s;
    int id, found = 0;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter ID to delete: ");
    id = getValidInt();

    while (fscanf(fp, "%d,%49[^,],%f\n", &s.id, s.name, &s.marks) == 3) {
        if (s.id != id) {
            fprintf(temp, "%d,%s,%.2f\n", s.id, s.name, s.marks);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("Record deleted successfully!\n");
    else
        printf("Student not found!\n");
}

// Update student
void updateStudent() {
    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Student s;
    int id, found = 0;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter ID to update: ");
    id = getValidInt();

    while (fscanf(fp, "%d,%49[^,],%f\n", &s.id, s.name, &s.marks) == 3) {
        if (s.id == id) {
            printf("Enter new name: ");
            getValidString(s.name, sizeof(s.name));

            printf("Enter new marks: ");
            s.marks = getValidFloat();

            found = 1;
        }
        fprintf(temp, "%d,%s,%.2f\n", s.id, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("Record updated successfully!\n");
    else
        printf("Student not found!\n");
}

// Main menu
int main() {
    int choice;

    do {
        printf("\n--- Student Record Manager ---\n");
        printf("1. Add Student\n");
        printf("2. Display All\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter choice: ");

        choice = getValidInt();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}
