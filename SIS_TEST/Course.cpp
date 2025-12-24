// Course.cpp
// Implements Course class logic

#include "Course.h"
#include <sstream>

using namespace std;

// ===============================
// Constructors
// ===============================
Course::Course() {
    practical = false;
    outOf = 100;
}

Course::Course(const string& c,
    const string& n,
    bool isPractical,
    int out) {
    code = c;
    name = n;
    practical = isPractical;
    outOf = out;
}

// ===============================
// Getters
// ===============================
string Course::getCode() const {
    return code;
}

string Course::getName() const {
    return name;
}

bool Course::isPractical() const {
    return practical;
}

int Course::getOutOf() const {
    return outOf;
}

// ===============================
// View
// ===============================
void Course::printCourseInfo() const {
    cout << "Course Code : " << code << endl;
    cout << "Course Name : " << name << endl;
    cout << "Type        : "
        << (practical ? "Practical" : "Theoretical") << endl;
    cout << "Out Of      : " << outOf << endl;
}

// ===============================
// File Handling
// ===============================
// Format:
// code|name|practical|outOf
string Course::toFileString() const {
    ostringstream oss;
    oss << code << "|" << name << "|"
        << (practical ? 1 : 0) << "|"
        << outOf;
    return oss.str();
}

Course Course::fromFileString(const string& line) {
    Course c;
    string token;
    istringstream iss(line);

    getline(iss, c.code, '|');
    getline(iss, c.name, '|');

    getline(iss, token, '|');
    c.practical = (token == "1");

    getline(iss, token, '|');
    c.outOf = stoi(token);

    return c;
}
