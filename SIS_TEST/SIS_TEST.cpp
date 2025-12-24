// main.cpp
// University Student Information System (SIS)
// Console Application (CLI) - C++17

#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "Student.h"
#include "Professor.h"
#include "Course.h"
#include "Admin.h"
#include "FileManager.h"

using namespace std;

// ===================================================
// Utilities
// ===================================================
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool continueProgram() {
    string c;
    cout << "\nPress N to perform another operation or type 'exit' to quit: ";
    getline(cin, c);
    return (c != "exit");
}

// ===================================================
// LOGIN FUNCTIONS
// ===================================================
Student* studentLogin(vector<Student>& students) {
    clearScreen();
    string id;
    cout << "===== Student Login =====\n";
    cout << "Enter Student ID: ";
    getline(cin, id);

    for (auto& s : students) {
        if (s.getId() == id)
            return &s;
    }

    cout << "Student not found.\n";
    pause();
    return nullptr;
}

Professor* professorLogin(vector<Professor>& professors) {
    clearScreen();
    string id;
    cout << "===== Professor Login =====\n";
    cout << "Enter Professor ID: ";
    getline(cin, id);

    for (auto& p : professors) {
        if (p.getId() == id)
            return &p;
    }

    cout << "Professor not found.\n";
    pause();
    return nullptr;
}

bool adminLogin() {
    clearScreen();
    string pass;
    cout << "===== Admin Login =====\n";
    cout << "Enter Admin Password: ";
    getline(cin, pass);
    return (pass == "admin123");   // academic static password
}

// ===================================================
// STUDENT SESSION
// ===================================================
void studentSession(Student& s) {
    while (true) {
        clearScreen();
        cout << "----- Student Menu -----\n";
        cout << "1. View personal data\n";
        cout << "2. View grades\n";
        cout << "3. View GPA\n";
        cout << "4. View tuition status\n";
        cout << "5. Back\n";
        cout << "Choice: ";

        string ch;
        getline(cin, ch);

        clearScreen();
        if (ch == "1") s.viewPersonalData();
        else if (ch == "2") s.viewGrades();
        else if (ch == "3") s.viewGPA();
        else if (ch == "4") s.viewTuitionStatus();
        else if (ch == "5") break;
        else cout << "Invalid choice.\n";

        pause();
    }
}

// ===================================================
// PROFESSOR SESSION
// ===================================================
void professorSession(
    Professor& p,
    vector<Student>& students,
    vector<Course>& courses,
    FileManager& fm
) {
    while (true) {
        clearScreen();
        cout << "----- Professor Menu -----\n";
        cout << "1. View assigned courses\n";
        cout << "2. Add / Update student grade\n";
        cout << "3. Delete student grade\n";
        cout << "4. Attendance tracking\n";
        cout << "5. View students grades & attendance\n";
        cout << "6. Back\n";
        cout << "Choice: ";

        string ch;
        getline(cin, ch);

        clearScreen();

        if (ch == "1") {
            p.viewAssignedCourses();
        }
        else if (ch == "2") {
            string sid, ccode;
            cout << "Student ID: ";
            getline(cin, sid);
            cout << "Course Code: ";
            getline(cin, ccode);

            Student* s = nullptr;
            Course* c = nullptr;

            for (auto& st : students)
                if (st.getId() == sid) s = &st;

            for (auto& co : courses)
                if (co.getCode() == ccode) c = &co;

            if (s && c) {
                p.addOrUpdateStudentGrade(*s, *c);
                fm.saveStudents(students);
                fm.logAction("Professor updated grade for student " + sid);
            }
            else {
                cout << "Student or course not found.\n";
            }
        }
        else if (ch == "3") {
            string sid, ccode;
            cout << "Student ID: ";
            getline(cin, sid);
            cout << "Course Code: ";
            getline(cin, ccode);

            for (auto& st : students)
                if (st.getId() == sid)
                    p.deleteStudentGrade(st, ccode);

            fm.saveStudents(students);
        }
        else if (ch == "4") {
            string sid, ccode;
            cout << "Student ID: ";
            getline(cin, sid);
            cout << "Course Code: ";
            getline(cin, ccode);

            Student* s = nullptr;
            Course* c = nullptr;

            for (auto& st : students)
                if (st.getId() == sid) s = &st;

            for (auto& co : courses)
                if (co.getCode() == ccode) c = &co;

            if (s && c) {
                p.markAttendance(*s, *c);
                fm.saveStudents(students);
            }
            else {
                cout << "Student or course not found.\n";
            }
        }
        else if (ch == "5") {
            string ccode;
            cout << "Course Code: ";
            getline(cin, ccode);

            for (auto& c : courses)
                if (c.getCode() == ccode)
                    p.viewStudentsGradesAndAttendance(students, c);
        }
        else if (ch == "6") break;
        else {
            cout << "Invalid choice.\n";
        }

        pause();
    }
}

// ===================================================
// ADMIN SESSION
// ===================================================
void adminSession(Admin& admin, FileManager& fm) {
    while (true) {
        clearScreen();
        cout << "----- Administration Menu -----\n";
        cout << "1. Add student\n";
        cout << "2. Update student\n";
        cout << "3. Delete student\n";
        cout << "4. Add course\n";
        cout << "5. Delete course\n";
        cout << "6. Add professor\n";
        cout << "7. Assign professor to course\n";
        cout << "8. View all students\n";
        cout << "9. View all courses\n";
        cout << "10. View all professors\n";
        cout << "11. View faculties & departments\n";
        cout << "12. Manage student fees\n";
        cout << "13. Back\n";
        cout << "Choice: ";

        string ch;
        getline(cin, ch);

        clearScreen();

        if (ch == "1") admin.addStudent(fm);
        else if (ch == "2") admin.updateStudent(fm);
        else if (ch == "3") admin.deleteStudent(fm);
        else if (ch == "4") admin.addCourse(fm);
        else if (ch == "5") admin.deleteCourse(fm);
        else if (ch == "6") admin.addProfessor(fm);
        else if (ch == "7") admin.assignProfessorToCourse(fm);
        else if (ch == "8") admin.viewAllStudents(fm);
        else if (ch == "9") admin.viewAllCourses(fm);
        else if (ch == "10") admin.viewAllProfessors(fm);
        else if (ch == "11") {
            admin.viewFaculties();
            admin.viewDepartments();
        }
        else if (ch == "12") admin.manageStudentFees(fm);
        else if (ch == "13") break;
        else cout << "Invalid choice.\n";

        pause();
    }
}

// ===================================================
// MAIN
// ===================================================
int main() {
    FileManager fm;
    Admin admin;
    bool running = true;

    while (running) {
        clearScreen();

        vector<Student> students = fm.loadStudents();
        vector<Course> courses = fm.loadCourses();
        vector<Professor> professors = fm.loadProfessors();

        cout << "===== University SIS =====\n";
        cout << "1. Student\n";
        cout << "2. Professor\n";
        cout << "3. Admin\n";
        cout << "4. Exit\n";
        cout << "Choice: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            Student* s = studentLogin(students);
            if (s) studentSession(*s);
            fm.saveStudents(students);
        }
        else if (choice == "2") {
            Professor* p = professorLogin(professors);
            if (p) professorSession(*p, students, courses, fm);
            fm.saveStudents(students);
        }
        else if (choice == "3") {
            if (adminLogin())
                adminSession(admin, fm);
            else {
                cout << "Wrong admin password.\n";
                pause();
            }
        }
        else if (choice == "4" || choice == "exit") {
            running = false;
        }
        else {
            cout << "Invalid choice.\n";
            pause();
        }

        if (running)
            running = continueProgram();
    }

    clearScreen();
    cout << "Program closed successfully.\n";
    return 0;
}
