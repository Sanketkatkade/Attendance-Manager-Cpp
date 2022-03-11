#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to mark attendance for a student
void markAttendance(vector<int>& rollNumbers, vector<string>& names, vector<bool>& attendance) {
    int roll;
    cout << "Enter the roll number of the student: ";
    cin >> roll;

    bool found = false;
    for (size_t i = 0; i < rollNumbers.size(); ++i) {
        if (rollNumbers[i] == roll) {
            found = true;
            cout << "Enter 'P' for Present or 'A' for Absent: ";
            char choice;
            cin >> choice;
            if (choice == 'P' || choice == 'p') {
                attendance[i] = true;
                cout << "Attendance marked for " << names[i] << endl;
            } else if (choice == 'A' || choice == 'a') {
                attendance[i] = false;
                cout << "Attendance marked (Absent) for " << names[i] << endl;
            } else {
                cout << "Invalid choice. Attendance not marked." << endl;
            }
        }
    }

    if (!found) {
        cout << "Student with roll number " << roll << " not found." << endl;
    }
}

// Function to display attendance report
void displayAttendanceReport(const vector<int>& rollNumbers, const vector<string>& names, const vector<bool>& attendance) {
    cout << "Attendance Report:" << endl;
    for (size_t i = 0; i < rollNumbers.size(); ++i) {
        cout << "Roll Number: " << rollNumbers[i]
                  << ", Name: " << names[i]
                  << ", Attendance: " << (attendance[i] ? "Present" : "Absent")
                  << endl;
    }
}

int main() {
    vector<int> rollNumbers = {101, 102, 103};
    vector<string> names = {"Alice", "Bob", "Charlie"};
    vector<bool> attendance(rollNumbers.size(), false);

    int choice;
    do {
        cout << "\nStudent Attendance Management System\n";
        cout << "1. Mark Attendance\n";
        cout << "2. Display Attendance Report\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                markAttendance(rollNumbers, names, attendance);
                break;
            case 2:
                displayAttendanceReport(rollNumbers, names, attendance);
                break;
            case 3:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 3);

    return 0;
}
