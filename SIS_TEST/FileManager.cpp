// FileManager.cpp
// Handles Read / Write / Update / Delete + Logging
// All data stored in D:\

#define _CRT_SECURE_NO_WARNINGS   // to avoid ctime warning on Windows

#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;

// ===============================
// LOGGING
// ===============================
void FileManager::logAction(const string& action) {
    ofstream file(logFile, ios::app);
    if (!file.is_open()) return;

    time_t now = time(nullptr);
    file << ctime(&now) << " -> " << action << endl;
    file.close();
}

// ===============================
// STUDENTS
// ===============================
vector<Student> FileManager::loadStudents() {
    vector<Student> students;
    ifstream file(studentsFile);

    if (!file.is_open())
        return students;

    string line;
    while (getline(file, line)) {
        if (!line.empty())
            students.push_back(Student::fromFileString(line));
    }

    file.close();
    logAction("Loaded students");
    return students;
}

void FileManager::saveStudents(const vector<Student>& students) {
    ofstream file(studentsFile, ios::trunc);
    if (!file.is_open()) return;

    for (const auto& s : students)
        file << s.toFileString() << endl;

    file.close();
    logAction("Saved students");
}

// ===============================
// COURSES
// ===============================
vector<Course> FileManager::loadCourses() {
    vector<Course> courses;
    ifstream file(coursesFile);

    if (!file.is_open())
        return courses;

    string line;
    while (getline(file, line)) {
        if (!line.empty())
            courses.push_back(Course::fromFileString(line));
    }

    file.close();
    logAction("Loaded courses");
    return courses;
}

void FileManager::saveCourses(const vector<Course>& courses) {
    ofstream file(coursesFile, ios::trunc);
    if (!file.is_open()) return;

    for (const auto& c : courses)
        file << c.toFileString() << endl;

    file.close();
    logAction("Saved courses");
}

// ===============================
// PROFESSORS
// ===============================
vector<Professor> FileManager::loadProfessors() {
    vector<Professor> professors;
    ifstream file(professorsFile);

    if (!file.is_open())
        return professors;

    string line;
    while (getline(file, line)) {
        if (!line.empty())
            professors.push_back(Professor::fromFileString(line));
    }

    file.close();
    logAction("Loaded professors");
    return professors;
}

void FileManager::saveProfessors(const vector<Professor>& professors) {
    ofstream file(professorsFile, ios::trunc);
    if (!file.is_open()) return;

    for (const auto& p : professors)
        file << p.toFileString() << endl;

    file.close();
    logAction("Saved professors");
}

// ===============================
// DELETE OPERATIONS
// ===============================
void FileManager::deleteStudentById(const string& id) {
    vector<Student> students = loadStudents();
    vector<Student> updated;

    for (const auto& s : students) {
        if (s.getId() != id)
            updated.push_back(s);
    }

    saveStudents(updated);
    logAction("Deleted student ID: " + id);
}

void FileManager::deleteCourseByCode(const string& code) {
    vector<Course> courses = loadCourses();
    vector<Course> updated;

    for (const auto& c : courses) {
        if (c.getCode() != code)
            updated.push_back(c);
    }

    saveCourses(updated);
    logAction("Deleted course code: " + code);
}

void FileManager::deleteProfessorById(const string& id) {
    vector<Professor> professors = loadProfessors();
    vector<Professor> updated;

    for (const auto& p : professors) {
        if (p.getId() != id)
            updated.push_back(p);
    }

    saveProfessors(updated);
    logAction("Deleted professor ID: " + id);
}
