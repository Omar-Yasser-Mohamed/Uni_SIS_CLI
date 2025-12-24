// Admin.cpp
// Full Administration Logic with REAL update implementation

#include "Admin.h"
#include <iostream>

using namespace std;

// ===================================================
// ADD STUDENT
// ===================================================
void Admin::addStudent(FileManager& fm) {
    vector<Student> students = fm.loadStudents();

    string id, name, dept;
    int year, level;

    cout << "Student ID: ";
    getline(cin, id);

    cout << "Student Name: ";
    getline(cin, name);

    cout << "Department: ";
    getline(cin, dept);

    cout << "Academic Year: ";
    cin >> year;

    cout << "Academic Level: ";
    cin >> level;
    cin.ignore();

    Student s(id, name);
    s.setDepartment(dept);
    s.setAcademicYear(year);
    s.setAcademicLevel(level);

    students.push_back(s);
    fm.saveStudents(students);
    fm.logAction("Admin added student " + id);

    cout << "Student added successfully.\n";
}

// ===================================================
// UPDATE STUDENT (REAL UPDATE)
// ===================================================
void Admin::updateStudent(FileManager& fm) {
    vector<Student> students = fm.loadStudents();
    string id;

    cout << "Enter Student ID to update: ";
    getline(cin, id);

    for (auto& s : students) {
        if (s.getId() == id) {

            string input;

            cout << "\n--- Updating Student ---\n";
            cout << "Current Name: " << s.getName() << endl;
            cout << "New Name (press Enter to keep current): ";
            getline(cin, input);
            if (!input.empty())
                s.setName(input);

            cout << "Current Department: " << s.getDepartment() << endl;
            cout << "New Department (press Enter to keep current): ";
            getline(cin, input);
            if (!input.empty())
                s.setDepartment(input);

            cout << "Current Academic Year: " << s.getAcademicYear() << endl;
            cout << "New Academic Year (press Enter to keep current): ";
            getline(cin, input);
            if (!input.empty())
                s.setAcademicYear(stoi(input));

            cout << "Current Academic Level: " << s.getAcademicLevel() << endl;
            cout << "New Academic Level (press Enter to keep current): ";
            getline(cin, input);
            if (!input.empty())
                s.setAcademicLevel(stoi(input));

            cout << "Current Tuition Status: "
                << (s.isTuitionPaid() ? "PAID" : "NOT PAID") << endl;
            cout << "Mark Tuition Paid? (y/n or Enter to keep): ";
            getline(cin, input);
            if (!input.empty())
                s.setTuitionPaid(input == "y" || input == "Y");

            fm.saveStudents(students);
            fm.logAction("Admin updated student " + id);

            cout << "\nStudent updated successfully.\n";
            return;
        }
    }

    cout << "Student not found.\n";
}

// ===================================================
// DELETE STUDENT
// ===================================================
void Admin::deleteStudent(FileManager& fm) {
    string id;
    cout << "Enter Student ID to delete: ";
    getline(cin, id);

    fm.deleteStudentById(id);
    fm.logAction("Admin deleted student " + id);

    cout << "Student deleted successfully.\n";
}

// ===================================================
// ADD PROFESSOR
// ===================================================
void Admin::addProfessor(FileManager& fm) {
    vector<Professor> professors = fm.loadProfessors();

    string id, name;
    cout << "Professor ID: ";
    getline(cin, id);

    cout << "Professor Name: ";
    getline(cin, name);

    professors.emplace_back(id, name);
    fm.saveProfessors(professors);
    fm.logAction("Admin added professor " + id);

    cout << "Professor added successfully.\n";
}

// ===================================================
// ASSIGN PROFESSOR TO COURSE
// ===================================================
void Admin::assignProfessorToCourse(FileManager& fm) {
    vector<Professor> professors = fm.loadProfessors();
    vector<Course> courses = fm.loadCourses();

    string pid, ccode;
    cout << "Professor ID: ";
    getline(cin, pid);

    cout << "Course Code: ";
    getline(cin, ccode);

    for (auto& p : professors) {
        if (p.getId() == pid) {
            p.assignCourse(ccode);
            fm.saveProfessors(professors);
            fm.logAction("Assigned professor " + pid + " to course " + ccode);
            cout << "Course assigned successfully.\n";
            return;
        }
    }

    cout << "Professor not found.\n";
}

// ===================================================
// ADD COURSE
// ===================================================
void Admin::addCourse(FileManager& fm) {
    vector<Course> courses = fm.loadCourses();

    string code, name;
    char practical;
    int outOf;

    cout << "Course Code: ";
    getline(cin, code);

    cout << "Course Name: ";
    getline(cin, name);

    cout << "Is Practical? (y/n): ";
    cin >> practical;

    cout << "Out Of (100 or 150): ";
    cin >> outOf;
    cin.ignore();

    Course c(code, name, (practical == 'y' || practical == 'Y'), outOf);
    courses.push_back(c);

    fm.saveCourses(courses);
    fm.logAction("Admin added course " + code);

    cout << "Course added successfully.\n";
}

// ===================================================
// DELETE COURSE
// ===================================================
void Admin::deleteCourse(FileManager& fm) {
    string code;
    cout << "Enter Course Code to delete: ";
    getline(cin, code);

    fm.deleteCourseByCode(code);
    fm.logAction("Admin deleted course " + code);

    cout << "Course deleted successfully.\n";
}

// ===================================================
// VIEW ALL STUDENTS
// ===================================================
void Admin::viewAllStudents(FileManager& fm) {
    vector<Student> students = fm.loadStudents();

    cout << "\n===== All Students =====\n";
    for (const auto& s : students) {
        cout << "ID: " << s.getId()
            << " | Name: " << s.getName()
            << " | Dept: " << s.getDepartment()
            << " | Level: " << s.getAcademicLevel()
            << " | Fees: " << (s.isTuitionPaid() ? "PAID" : "NOT PAID")
            << endl;
    }
}

// ===================================================
// VIEW ALL COURSES
// ===================================================
void Admin::viewAllCourses(FileManager& fm) {
    vector<Course> courses = fm.loadCourses();

    cout << "\n===== All Courses =====\n";
    for (const auto& c : courses) {
        c.printCourseInfo();
        cout << "----------------------\n";
    }
}

// ===================================================
// VIEW ALL PROFESSORS
// ===================================================
void Admin::viewAllProfessors(FileManager& fm) {
    vector<Professor> professors = fm.loadProfessors();

    cout << "\n===== All Professors =====\n";
    for (const auto& p : professors) {
        cout << "ID: " << p.getId()
            << " | Name: " << p.getName() << endl;
        p.viewAssignedCourses();
        cout << "----------------------\n";
    }
}

// ===================================================
// ACADEMIC STRUCTURE
// ===================================================
void Admin::viewFaculties() const {
    cout << "\nFaculties:\n";
    for (const auto& f : faculties)
        cout << "- " << f << endl;
}

void Admin::viewDepartments() const {
    cout << "\nDepartments:\n";
    for (const auto& d : departments)
        cout << "- " << d << endl;
}

// ===================================================
// MANAGE FEES
// ===================================================
void Admin::manageStudentFees(FileManager& fm) {
    vector<Student> students = fm.loadStudents();
    string id;

    cout << "Enter Student ID: ";
    getline(cin, id);

    for (auto& s : students) {
        if (s.getId() == id) {
            char ch;
            cout << "Mark fees as PAID? (y/n): ";
            cin >> ch;
            cin.ignore();

            s.setTuitionPaid(ch == 'y' || ch == 'Y');
            fm.saveStudents(students);
            fm.logAction("Admin updated fees for student " + id);

            cout << "Fees updated successfully.\n";
            return;
        }
    }

    cout << "Student not found.\n";
}
