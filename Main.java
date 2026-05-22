import java.io.*;
import java.util.*;

class Student {
    int id;
    String name;
    float marks;
}

public class Main {

    static Scanner sc = new Scanner(System.in);

    // Safe integer input
    static int getValidInt() {
        while (true) {
            String input = sc.nextLine();
            try {
                if (input.matches("\\d+")) {
                    return Integer.parseInt(input);
                } else {
                    throw new Exception();
                }
            } catch (Exception e) {
                System.out.print("Invalid input! Enter a valid integer: ");
            }
        }
    }

    // Safe float input
    static float getValidFloat() {
        while (true) {
            String input = sc.nextLine();
            try {
                return Float.parseFloat(input);
            } catch (Exception e) {
                System.out.print("Invalid input! Enter valid marks: ");
            }
        }
    }

    // Add student
    static void addStudent() throws IOException {
        File file = new File("students.txt");
        Scanner fileReader = null;

        int newId;
        boolean found = false;

        System.out.print("Enter ID: ");
        newId = getValidInt();

        if (file.exists()) {
            fileReader = new Scanner(file);

            while (fileReader.hasNextLine()) {
                String[] parts = fileReader.nextLine().split(",");

                if (Integer.parseInt(parts[0]) == newId) {
                    found = true;
                    break;
                }
            }
            fileReader.close();
        }

        if (found) {
            System.out.println("ID already exists!");
            return;
        }

        FileWriter fw = new FileWriter(file, true);

        Student s = new Student();
        s.id = newId;

        System.out.print("Enter Name: ");
        s.name = sc.nextLine();

        System.out.print("Enter Marks: ");
        s.marks = getValidFloat();

        fw.write(s.id + "," + s.name + "," + s.marks + "\n");
        fw.close();

        System.out.println("Student added successfully!");
    }

    // Display students
    static void displayStudents() throws IOException {
        File file = new File("students.txt");

        if (!file.exists()) {
            System.out.println("No records found!");
            return;
        }

        Scanner fileReader = new Scanner(file);

        System.out.println("\n--- Student Records ---");

        while (fileReader.hasNextLine()) {
            String[] parts = fileReader.nextLine().split(",");
            System.out.println("ID: " + parts[0] +
                               " | Name: " + parts[1] +
                               " | Marks: " + parts[2]);
        }

        fileReader.close();
    }

    // Search student
    static void searchStudent() throws IOException {
        File file = new File("students.txt");

        if (!file.exists()) {
            System.out.println("No records found!");
            return;
        }

        Scanner fileReader = new Scanner(file);

        System.out.print("Enter ID to search: ");
        int id = getValidInt();

        boolean found = false;

        while (fileReader.hasNextLine()) {
            String[] parts = fileReader.nextLine().split(",");

            if (Integer.parseInt(parts[0]) == id) {
                System.out.println("Found: " + parts[1] + " (Marks: " + parts[2] + ")");
                found = true;
                break;
            }
        }

        if (!found)
            System.out.println("Student not found!");

        fileReader.close();
    }

    // Delete student
    static void deleteStudent() throws IOException {
        File file = new File("students.txt");
        File temp = new File("temp.txt");

        if (!file.exists()) {
            System.out.println("No records found!");
            return;
        }

        Scanner fileReader = new Scanner(file);
        FileWriter fw = new FileWriter(temp);

        System.out.print("Enter ID to delete: ");
        int id = getValidInt();

        boolean found = false;

        while (fileReader.hasNextLine()) {
            String line = fileReader.nextLine();
            String[] parts = line.split(",");

            if (Integer.parseInt(parts[0]) != id) {
                fw.write(line + "\n");
            } else {
                found = true;
            }
        }

        fileReader.close();
        fw.close();

        file.delete();
        temp.renameTo(file);

        if (found)
            System.out.println("Record deleted successfully!");
        else
            System.out.println("Student not found!");
    }

    // Update student
    static void updateStudent() throws IOException {
        File file = new File("students.txt");
        File temp = new File("temp.txt");

        if (!file.exists()) {
            System.out.println("No records found!");
            return;
        }

        Scanner fileReader = new Scanner(file);
        FileWriter fw = new FileWriter(temp);

        System.out.print("Enter ID to update: ");
        int id = getValidInt();

        boolean found = false;

        while (fileReader.hasNextLine()) {
            String line = fileReader.nextLine();
            String[] parts = line.split(",");

            if (Integer.parseInt(parts[0]) == id) {
                System.out.print("Enter new name: ");
                String name = sc.nextLine();

                System.out.print("Enter new marks: ");
                float marks = getValidFloat();

                fw.write(id + "," + name + "," + marks + "\n");
                found = true;
            } else {
                fw.write(line + "\n");
            }
        }

        fileReader.close();
        fw.close();

        file.delete();
        temp.renameTo(file);

        if (found)
            System.out.println("Record updated successfully!");
        else
            System.out.println("Student not found!");
    }

    // Main menu
    public static void main(String[] args) throws IOException {
        int choice;

        do {
            System.out.println("\n--- Student Record Manager ---");
            System.out.println("1. Add Student");
            System.out.println("2. Display All");
            System.out.println("3. Search Student");
            System.out.println("4. Update Student");
            System.out.println("5. Delete Student");
            System.out.println("6. Exit");
            System.out.print("Enter choice: ");

            choice = getValidInt();

            switch (choice) {
                case 1: addStudent(); break;
                case 2: displayStudents(); break;
                case 3: searchStudent(); break;
                case 4: updateStudent(); break;
                case 5: deleteStudent(); break;
                case 6: System.out.println("Exiting..."); break;
                default: System.out.println("Invalid choice!");
            }

        } while (choice != 6);
    }
}
