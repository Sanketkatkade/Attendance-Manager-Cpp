#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <map>

using namespace std;

class Student {
public:
    string name;
    int rollNumber;
    map<string, char> attendance;

    Student(string name, int rollNumber) {
        this->name = name;
        this->rollNumber = rollNumber;
    }
};

class AttendanceSystem {
private:
    vector<Student> students;

public:
    void addStudent() {
        string name;
        int rollNumber;
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter student roll number: ";
        cin >> rollNumber;

        students.push_back(Student(name, rollNumber));
        cout << "Student added successfully!" << endl;

        // Save all student info to a CSV file
        saveToCSV("student_info.csv");
    }

    void markAttendance() {
        int rollNumber;
        cout << "Enter student roll number to mark attendance: ";
        cin >> rollNumber;

        auto it = find_if(students.begin(), students.end(),
            [rollNumber](const Student& student) {
                return student.rollNumber == rollNumber;
            });

        if (it != students.end()) {
            char status;
            cout << "Enter attendance status (P for present, A for absent): ";
            cin >> status;

            time_t now = time(0);
            tm* date = localtime(&now);
            char dateStr[11];
            strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", date);

            // Store attendance date-wise
            it->attendance[dateStr] = status;
            cout << "Attendance marked for roll number " << rollNumber << endl;

            saveToCSV("student_info.csv");
        } else {
            cout << "Student not found!" << endl;
        }
    }

    void saveToCSV(const string& filename) {
        ofstream outFile(filename);

        if (outFile.is_open()) {
            outFile << "Roll Number,Name";

            // Write the date headers
            vector<string> dates;
            for (const Student& student : students) {
                for (const auto& entry : student.attendance) {
                    dates.push_back(entry.first);
                }
            }
            sort(dates.begin(), dates.end());
            dates.erase(unique(dates.begin(), dates.end()), dates.end());

            for (const string& date : dates) {
                outFile << "," << date;
            }

            outFile << endl;

            for (const Student& student : students) {
                outFile << student.rollNumber << "," << student.name;

                for (const string& date : dates) {
                    if (student.attendance.find(date) != student.attendance.end()) {
                        outFile << "," << student.attendance.find(date)->second;
                    } else {
                        outFile << ",";
                    }
                }

                outFile << endl;
            }

            outFile.close();
        } else {
            cout << "Unable to open the file for writing." << endl;
        }
    }

    void displayAttendanceReport() {
        ifstream inFile("student_info.csv");
        if (!inFile.is_open()) {
            cout << "Unable to open the student_info.csv file." << endl;
            return;
        }

        cout << "Attendance Report:" << endl;
        cout << "---------------------------------------" << endl;

        string line;
        getline(inFile, line);

        cout << setw(12) << left << "Roll Number" << setw(12) << left << "Name";

        stringstream headerStream(line);
        string cell;
        while (getline(headerStream, cell, ',')) {
            if (cell != "Roll Number" && cell != "Name") {
                cout << setw(6) << cell;
            }
        }

        cout << endl;

        while (getline(inFile, line)) {
            istringstream iss(line);
            string roll, name, attendance;
            getline(iss, roll, ',');
            getline(iss, name, ',');

            cout << setw(12) << left << roll << setw(12) << left << name;

            while (getline(iss, attendance, ',')) {
                if (attendance != "Roll Number" && attendance != "Name") {
                    cout << setw(6) << attendance;
                }
            }

            cout << endl;
        }

        inFile.close();
    }
};

int main() {
    AttendanceSystem system;

    int choice;

    while (true) {
        cout << "\nAttendance Management System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Mark Attendance" << endl;
        cout << "3. Display Attendance Report" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.addStudent();
                break;
            case 2:
                system.markAttendance();
                break;
            case 3:
                system.displayAttendanceReport();
                break;
            case 4:
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
