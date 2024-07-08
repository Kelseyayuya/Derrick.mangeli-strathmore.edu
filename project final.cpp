#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Student {
    string firstname;
    string surname;
    string gender;
    int age;
    int group;
    vector<string> activities;
};

struct Activity {
    string name;
    int maxCapacity;
    int currentCapacity;
    int maxMale;
    int maxFemale;
    int currentMale;
    int currentFemale;
};

vector<Student> students;
vector<Activity> sports = {
        {"Rugby", 20, 0, 15, 5, 0, 0},
        {"Athletics", 20, 0, 15, 5, 0, 0},
        {"Swimming", 20, 0, 15, 5, 0, 0},
        {"Soccer", 20, 0, 15, 5, 0, 0}
};

vector<Activity> clubs = {
        {"Journalism Club", 60, 0, 30, 30, 0, 0},
        {"Red Cross Society", 60, 0, 30, 30, 0, 0},
        {"AISEC", 60, 0, 30, 30, 0, 0},
        {"Business Club", 60, 0, 30, 30, 0, 0},
        {"Computer Science Club", 60, 0, 30, 30, 0, 0}
};

void displayMenu() {
    cout << "1. Add Student" << endl;
    cout << "2. View Students" << endl;
    cout << "3. View Clubs/ Societies" << endl;
    cout << "4. View Sports" << endl;
    cout << "5. View allocated activities" << endl;
    cout << "6. Save all Files" << endl;
    cout << "7. Exit" << endl;
    cout << "Select an option: ";
}

void addStudent() {
    Student student;
    cout << "Enter Firstname: ";
    cin >> student.firstname;
    cout << "Enter Surname: ";
    cin >> student.surname;
    cout << "Enter Gender (Male/Female): ";
    cin >> student.gender;
    cout << "Enter Age: ";
    cin >> student.age;
    cout << "Enter BBIT Group (1, 2, or 3): ";
    cin >> student.group;

    if (student.group < 1 || student.group > 3) {
        cout << "Invalid group number. Adding student failed." << endl;
        return;
    }

    char choice;
    do {
        cout << "Select Activity Type: (S)port or (C)lub: ";
        cin >> choice;
        choice = tolower(choice);

        if (choice == 's') {
            cout << "Select Sport (1-Rugby, 2-Athletics, 3-Swimming, 4-Soccer): ";
            int sportChoice;
            cin >> sportChoice;

            if (sportChoice < 1 || sportChoice > 4) {
                cout << "Invalid sport choice." << endl;
            } else {
                Activity& sport = sports[sportChoice - 1];
                if (sport.currentCapacity < sport.maxCapacity) {
                    if ((student.gender == "Male" && sport.currentMale < sport.maxMale) ||
                        (student.gender == "Female" && sport.currentFemale < sport.maxFemale)) {
                        student.activities.push_back(sport.name);
                        sport.currentCapacity++;
                        if (student.gender == "Male") sport.currentMale++;
                        else sport.currentFemale++;
                        cout << "Added to " << sport.name << endl;
                    } else {
                        cout << "Gender capacity reached for " << sport.name << endl;
                    }
                } else {
                    cout << sport.name << " is full." << endl;
                }
            }
        } else if (choice == 'c') {
            cout << "Select Club (1-Journalism Club, 2-Red Cross Society, 3-AISEC, 4-Business Club, 5-Computer Science Club): ";
            int clubChoice;
            cin >> clubChoice;

            if (clubChoice < 1 || clubChoice > 5) {
                cout << "Invalid club choice." << endl;
            } else {
 Activity& club = clubs[clubChoice - 1];
                if (club.currentCapacity < club.maxCapacity) {
                    if ((student.gender == "Male" && club.currentMale < club.maxMale) ||
                        (student.gender == "Female" && club.currentFemale < club.maxFemale)) {
                        student.activities.push_back(club.name);
                        club.currentCapacity++;
                        if (student.gender == "Male") club.currentMale++;
                        else club.currentFemale++;
                        cout << "Added to " << club.name << endl;
                    } else {
                        cout << "Gender capacity reached for " << club.name << endl;
                    }
                } else {
                    cout << club.name << " is full." << endl;
                }
            }
        } else {
            cout << "Invalid choice." << endl;
        }

        cout << "Add another activity? (Y/N): ";
        cin >> choice;
        choice = tolower(choice);
    } while (choice == 'y' && student.activities.size() < 3);

    students.push_back(student);
    cout << "Student added successfully." << endl;
}

void viewStudents() {
    cout << "1. View All Students" << endl;
    cout << "2. View Students by Group" << endl;
    int choice;
    cin >> choice;

    if (choice == 1) {
        for (const auto& student : students) {
            cout << student.firstname << " " << student.surname << ", Group: " << student.group << ", Activities: ";
            for (const auto& activity : student.activities) {
                cout << activity << " ";
            }
            cout << endl;
        }
    } else if (choice == 2) {
        cout << "Enter group number (1, 2, or 3): ";
        int group;
        cin >> group;

        for (const auto& student : students) {
            if (student.group == group) {
                cout << student.firstname << " " << student.surname << ", Activities: ";
                for (const auto& activity : student.activities) {
                    cout << activity << " ";
                }
                cout << endl;
 }
        }
    } else {
        cout << "Invalid choice." << endl;
    }
}

void viewClubs() {
    for (const auto& club : clubs) {
        cout << club.name << " - Capacity: " << club.currentCapacity << "/" << club.maxCapacity << endl;
    }
}

void viewSports() {
    for (const auto& sport : sports) {
        cout << sport.name << " - Capacity: " << sport.currentCapacity << "/" << sport.maxCapacity << endl;
    }
}

void viewGroupedStudents() {
    vector<Student> group1, group2, group3;

    for (const auto& student : students) {
        if (student.group == 1) group1.push_back(student);
        else if (student.group == 2) group2.push_back(student);
        else if (student.group == 3) group3.push_back(student);
    }

    cout << "Group 1:" << endl;
    for (const auto& student : group1) {
        cout << student.firstname << " " << student.surname << ", Activities: ";
        for (const auto& activity : student.activities) {
            cout << activity << " ";
        }
        cout << endl;
    }

    cout << "Group 2:" << endl;
    for (const auto& student : group2) {
        cout << student.firstname << " " << student.surname << ", Activities: ";
        for (const auto& activity : student.activities) {
            cout << activity << " ";
        }
        cout << endl;
    }
