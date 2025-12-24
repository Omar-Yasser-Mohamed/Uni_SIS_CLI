// Professor.cpp
// Implements Professor logic: grading, attendance, reports, file handling

#include "Professor.h"
#include <iostream>
#include <sstream>

using namespace std;

// ===============================
// Constructors
// ===============================
Professor::Professor() {}

Professor::Professor(const string& _id, const string& _name)
    : id(_id), name(_name) {
}

// ===============================
// Getters
// ===============================
string Professor::getId() const {
    return id;
}

string Professor::getName() const {
    return name;
}

// ===============================
// Course Assignment
// ===============================
void Professor::assignCourse(const string& courseCode) {
    assignedCourses.push_back(courseCode);
}

bool Professor::teachesCourse(const string& courseCode) const {
    for (const auto& c : assignedCourses) {
        if (c == courseCode)
            return true;
    }
    return false;
}

// ===============================
// View Assigned Courses
// ===============================
void Professor::viewAssignedCourses() const {
    cout << "\nCourses assigned to Professor " << name << ":\n";
    if (assignedCourses.empty()) {
        cout << "No courses assigned.\n";
        return;
    }

    for (const auto& c : assignedCourses)
        cout << "- " << c << endl;
}

// ===============================
// Add / Update Student Grade
// ===============================
void Professor::addOrUpdateStudentGrade(Student& s, const Course& c) {

    // Permission check
    if (!teachesCourse(c.getCode())) {
        cout << "\nERROR: You are not allowed to grade this course.\n";
        return;
    }

    // Find student's grade record
    CourseGrade* g = s.findCourseGrade(c.getCode());

    // If student is not registered in course → register
    if (!g) {
        CourseGrade newGrade;
        newGrade.courseCode = c.getCode();
        newGrade.isPractical = c.isPractical();
        newGrade.outOf = c.getOutOf();
        s.addOrUpdateGrade(newGrade);
        g = s.findCourseGrade(c.getCode());
    }

    // Choose grade type
    cout << "\n--- Select Grade Type ---\n";
    cout << "1. Assignment 1\n";
    cout << "2. Assignment 2\n";
    cout << "3. CW\n";
    cout << "4. Final Exam\n";
    cout << "Choice: ";

    string choice;
    getline(cin, choice);

    double value;
    cout << "Enter grade value: ";
    cin >> value;
    cin.ignore();

    // Validation
    if (value < 0 || value > g->outOf) {
        cout << "Invalid grade value.\n";
        return;
    }

    if (choice == "1") {
        g->ass1 = value;
        cout << "Assignment 1 updated.\n";
    }
    else if (choice == "2") {
        g->ass2 = value;
        cout << "Assignment 2 updated.\n";
    }
    else if (choice == "3") {
        g->cw = value;
        cout << "CW updated.\n";
    }
    else if (choice == "4") {
        g->finalExam = value;
        cout << "Final Exam updated.\n";
    }
    else {
        cout << "Invalid choice.\n";
    }
}

// ===============================
// Delete Student Grade (reset)
// ===============================
void Professor::deleteStudentGrade(Student& s, const string& courseCode) {

    if (!teachesCourse(courseCode)) {
        cout << "\nERROR: You are not allowed to modify this course.\n";
        return;
    }

    CourseGrade* g = s.findCourseGrade(courseCode);
    if (!g) {
        cout << "\nNo grade found for this course.\n";
        return;
    }

    g->ass1 = 0;
    g->ass2 = 0;
    g->cw = 0;
    g->finalExam = 0;

    cout << "\nGrade deleted successfully.\n";
}

// ===============================
// Attendance Tracking (per course)
// ===============================
void Professor::markAttendance(Student& s, const Course& c) {

    if (!teachesCourse(c.getCode())) {
        cout << "\nERROR: You are not allowed to mark attendance for this course.\n";
        return;
    }

    CourseGrade* g = s.findCourseGrade(c.getCode());
    if (!g) {
        cout << "\nStudent is not registered in this course.\n";
        return;
    }

    g->totalLectures++;

    char status;
    cout << "Mark attendance for " << s.getName() << " (P/A): ";
    cin >> status;
    cin.ignore();

    if (status == 'P' || status == 'p') {
        g->attendedLectures++;
        cout << "Marked PRESENT.\n";
    }
    else {
        cout << "Marked ABSENT.\n";
    }
}

// ===============================
// View Students Grades & Attendance
// ===============================
void Professor::viewStudentsGradesAndAttendance(
    const vector<Student>& students,
    const Course& course
) const {

    if (!teachesCourse(course.getCode())) {
        cout << "\nERROR: You do not teach this course.\n";
        return;
    }

    cout << "\n=== Students Grades & Attendance ===\n";
    cout << "Course: " << course.getCode()
        << " - " << course.getName() << "\n\n";

    bool found = false;

    for (const auto& s : students) {
        CourseGrade* g =
            const_cast<Student&>(s).findCourseGrade(course.getCode());

        if (!g)
            continue;

        found = true;

        cout << "Student: " << s.getName()
            << " (ID: " << s.getId() << ")\n";

        cout << "  Ass1  : " << g->ass1 << "\n";
        cout << "  Ass2  : " << g->ass2 << "\n";
        cout << "  CW    : " << g->cw << "\n";
        cout << "  Final : " << g->finalExam << "\n";

        cout << "  Attendance: "
            << g->attendedLectures
            << " / " << g->totalLectures << "\n";

        cout << "-----------------------------\n";
    }

    if (!found) {
        cout << "No students registered in this course.\n";
    }
}

// ===============================
// File Handling
// ===============================
// Format:
// id|name|course1,course2,course3
string Professor::toFileString() const {
    ostringstream oss;
    oss << id << "|" << name << "|";

    for (size_t i = 0; i < assignedCourses.size(); i++) {
        oss << assignedCourses[i];
        if (i != assignedCourses.size() - 1)
            oss << ",";
    }

    return oss.str();
}

Professor Professor::fromFileString(const string& line) {
    Professor p;
    string token;
    istringstream iss(line);

    getline(iss, p.id, '|');
    getline(iss, p.name, '|');
    getline(iss, token, '|');

    istringstream cs(token);
    string c;
    while (getline(cs, c, ',')) {
        if (!c.empty())
            p.assignedCourses.push_back(c);
    }

    return p;
}
