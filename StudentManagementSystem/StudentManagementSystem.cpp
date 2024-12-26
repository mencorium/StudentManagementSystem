#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
using namespace std;

// Data Structure definition: We have used Structure called Student
/* this structure stores information name, age, and grade*/

struct Student {
    string name;
    int age;
    int grade;
};

// Function to validate integer input with try...catch
int getValidInteger(string description) {
    int value;
    while (true) {
        try {
            cout << description;
            cin >> value;

            if (cin.fail()) {
                throw runtime_error("Invalid input. Please enter a valid number.");
            }

            // Clear remaining input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        catch (const runtime_error& e) {
            // Handle the exception
            cout << e.what() << endl;

            // Clear the error state and discard invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Function to add students.
// It allow input from user validate them and then store the structure into array
void addStudents(Student*& students, int& count, int& capacity) {
    int noStudents;
    cout << "Number of Students to be Enrolled: ";
    noStudents = getValidInteger("");

    // Check if we need to expand the array
    if (count + noStudents > capacity) {
        int newCapacity = max(capacity * 2, count + noStudents);
        Student* newStudents = new Student[newCapacity];

        // Copy existing students to the new array.
        // Swapping is essential to append new date into array without overlapping of array
        for (int i = 0; i < count; i++) {
            newStudents[i] = students[i];
        }

        // Free old memory and update pointer
        delete[] students;
        students = newStudents;
        capacity = newCapacity;
    }

    // Add new students
    for (int i = 0; i < noStudents; i++) {
        cout << "\nEnter details for Student " << (count + 1) << ":" << endl;
        cout << "===========================================" << endl;

        cin.ignore(); // To clear the input buffer
        cout << "Name: ";
        getline(cin, students[count].name);

        students[count].age = getValidInteger("Age: ");

        students[count].grade = getValidInteger("Grade: ");
        while (students[count].grade < 0 || students[count].grade > 100) {
            cout << "Please enter a valid grade (0-100): ";
            students[count].grade = getValidInteger("Grade: ");
        }

        count++;
    }
}

// Function to display all students
// It uses simple traversing technique, also it accespt student pointer to get location from memory
// and count to know the lenght of array currently
void displayStudents(const Student* students, int count) {
    cout << "\nList of Enrolled Students:" << endl;
    cout << "===========================================" << endl;
    if (count == 0) {
        cout << "No students enrolled yet!" << endl;
    }
    for (int i = 0; i < count; i++) {
        cout << "Student " << (i + 1) << ":" << endl;
        cout << "Name: " << students[i].name << endl;
        cout << "Age: " << students[i].age << endl;
        cout << "Grade: " << students[i].grade << endl;
        cout << "-------------------------------------------" << endl;
    }
}

/* Utilities functions: these are functions for certain tasks*/
float calculateAverage(const Student* students, int count) {
    if (count == 0) {
        cout << "No students to calculate the average!" << endl;
        return 0.0f;
    }

    int totalGrade = 0;

    for (int i = 0; i < count; i++)
        totalGrade += students[i].grade;

    return static_cast<float>(totalGrade) / count;
}

int main() {
    int capacity = 2;   // Initial capacity of the array
    int count = 0;      // Current number of students
    Student* students = new Student[capacity]; // Dynamically allocated array
    int choice;

    cout << "\t\tSIMPLE STUDENT MANAGEMENT SYSTEM in C++"
        << "\nWith following functionality: add student, display students, and calculate average...\n"
        << "=====================================================================================";

    while (true) {
        cout << "\n\nStudent Management System Menu:\n"
            << "\t\t1. Add new Student(s).\n"
            << "\t\t2. List of Enrolled Students\n"
            << "\t\t3. Grade Average of all Students\n"
            << "\t\t4. Exit" << endl;

        choice = getValidInteger("Enter your Choice: ");
        cout << "\n\n";

        switch (choice) {
        case 1:
            addStudents(students, count, capacity);
            break;

        case 2:
            displayStudents(students, count);
            break;

        case 3:
            cout << "\n\nGrade Average: " << calculateAverage(students, count) << endl;
            break;

        case 4: {
            char confirmExit;
            cout << "\a\n\nAre you sure you want to leave? (y/n): ";
            cin >> confirmExit;

            if (confirmExit == 'y' || confirmExit == 'Y') {
                cout << "\nExiting the system. Goodbye!" << endl;
                delete[] students; // Free allocated memory
                return 0;  // Exit the program
            }
            else {
                cout << "\n\nReturning to the system.\n" << endl;
            }
            break;
        }

        default:
            cout << "\a\n\nInvalid input. Please enter a choice from 1-4\n\n";
            break;
        }
    }

    delete[] students; // Free allocated memory (unreachable code but kept for clarity)
    return 0;
}
