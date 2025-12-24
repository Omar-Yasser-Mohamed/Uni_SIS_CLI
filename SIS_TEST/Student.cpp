// Student.cpp
// Implements Student logic

#include "Student.h"
#include <sstream>
#include <iomanip>

using namespace std;

// ===============================
// Constructors
// ===============================
Student::Student() {
    academicYear = 1;
    academicLevel = 100;
    tuitionPaid = false;
}

Student::Student(const string& _id, const string& _name)
    : id(_id), name(_name), academicYear(1), academicLevel(100), tuitionPaid(false) {
}

// ===============================
// Getters
// ===============================
string Student::getId() const { return id; }
string Student::getName() const { return name; }
string Student::getDepartment() const { return department; }
int Student::getAcademicYear() const { return academicYear; }
int Student::getAcademicLevel() const { return academicLevel; }
bool Student::isTuitionPaid() const { return tuitionPaid; }

// ===============================
// Setters
// ===============================
void Student::setName(const string& n) { name = n; }
void Student::setDepartment(const string& d) { department = d; }
void Student::setAcademicYear(int y) { academicYear = y; }
void Student::setAcademicLevel(int l) { academicLevel = l; }
void Student::setTuitionPaid(bool paid) { tuitionPaid = paid; }

// ===============================
// Views
// ===============================
void Student::viewPersonalData() const {
    cout << "\n--- Student Data ---\n";
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Department: " << department << endl;
    cout << "Academic Year: " << academicYear << endl;
    cout << "Academic Level: " << academicLevel << endl;
}

void Student::viewTuitionStatus() const {
    cout << "\nTuition Status: "
        << (tuitionPaid ? "PAID" : "NOT PAID") << endl;
}

// ===============================
// Grades Logic
// ===============================
CourseGrade* Student::findCourseGrade(const string& courseCode) {
    for (auto& g : grades) {
        if (g.courseCode == courseCode)
            return &g;   // ✅ pointer usage
    }
    return nullptr;
}

void Student::addOrUpdateGrade(const CourseGrade& g) {
    CourseGrade* existing = findCourseGrade(g.courseCode);
    if (existing) {
        *existing = g;
    }
    else {
        grades.push_back(g);
    }
}

double Student::calculateCoursePercentage(const CourseGrade& g) const {
    double total = 0;

    if (g.isPractical) {
        total =
            g.ass1 * 0.20 +
            g.ass2 * 0.30 +
            g.cw * 0.20 +
            g.finalExam * 0.30;
    }
    else {
        total =
            g.ass1 * 0.20 +
            g.ass2 * 0.20 +
            g.cw * 0.60;
    }

    return total;
}

string Student::evaluateGrade(double percent) const {
    if (percent >= 85) return "Excellent";
    if (percent >= 75) return "Very Good";
    if (percent >= 65) return "Good";
    if (percent >= 60) return "Pass";
    return "Fail";
}

void Student::viewGrades() const {
    cout << "\n--- Grades ---\n";
    if (grades.empty()) {
        cout << "No grades available.\n";
        return;
    }

    for (const auto& g : grades) {
        double percent = calculateCoursePercentage(g);
        cout << "Course: " << g.courseCode
            << " | %: " << fixed << setprecision(2) << percent
            << " | Grade: " << evaluateGrade(percent)
            << endl;
    }
}

void Student::viewGPA() const {
    if (grades.empty()) {
        cout << "No GPA available.\n";
        return;
    }

    double sum = 0;
    for (const auto& g : grades)
        sum += calculateCoursePercentage(g);

    double avg = sum / grades.size();
    double gpa = (avg / 100.0) * 4.0;

    cout << "\nGPA: " << fixed << setprecision(2) << gpa << endl;
}

// ===============================
// File Handling
// ===============================
string Student::toFileString() const {
    ostringstream oss;
    oss << id << "|" << name << "|" << department << "|"
        << academicYear << "|" << academicLevel << "|"
        << tuitionPaid;

    for (const auto& g : grades) {
        oss << "|" << g.courseCode << ","
            << g.ass1 << "," << g.ass2 << ","
            << g.cw << "," << g.finalExam << ","
            << g.outOf << "," << g.isPractical;
    }

    return oss.str();
}

Student Student::fromFileString(const string& line) {
    Student s;
    stringstream ss(line);
    string token;

    getline(ss, s.id, '|');
    getline(ss, s.name, '|');
    getline(ss, s.department, '|');

    getline(ss, token, '|'); s.academicYear = stoi(token);
    getline(ss, token, '|'); s.academicLevel = stoi(token);
    getline(ss, token, '|'); s.tuitionPaid = (token == "1");

    while (getline(ss, token, '|')) {
        CourseGrade g;
        stringstream gs(token);
        string part;

        getline(gs, g.courseCode, ',');
        getline(gs, part, ','); g.ass1 = stod(part);
        getline(gs, part, ','); g.ass2 = stod(part);
        getline(gs, part, ','); g.cw = stod(part);
        getline(gs, part, ','); g.finalExam = stod(part);
        getline(gs, part, ','); g.outOf = stoi(part);
        getline(gs, part, ','); g.isPractical = (part == "1");

        s.grades.push_back(g);
    }

    return s;
}
