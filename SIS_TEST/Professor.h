#pragma once
// Professor.h
// Defines Professor class responsibilities

#include <string>
#include <vector>
#include "Student.h"
#include "Course.h"

// ===============================
// CLASS: Professor
// ===============================
class Professor {
private:
    std::string id;
    std::string name;

    // Courses assigned to this professor
    std::vector<std::string> assignedCourses;

public:
    // ===============================
    // Constructors
    // ===============================
    Professor();
    Professor(const std::string& _id, const std::string& _name);

    // ===============================
    // Getters
    // ===============================
    std::string getId() const;
    std::string getName() const;

    // ===============================
    // Course Assignment
    // ===============================
    void assignCourse(const std::string& courseCode);
    bool teachesCourse(const std::string& courseCode) const;

    // ===============================
    // View
    // ===============================
    void viewAssignedCourses() const;

    // ===============================
    // Grades Management
    // ===============================
    void addOrUpdateStudentGrade(Student& s, const Course& c);
    void deleteStudentGrade(Student& s, const std::string& courseCode);

    // ===============================
    // Attendance
    // ===============================
    void markAttendance(Student& s, const Course& c);

    // ===============================
    // Reports (Professor View)
    // ===============================
    void viewStudentsGradesAndAttendance(
        const std::vector<Student>& students,
        const Course& course
    ) const;

    // ===============================
    // File Handling
    // ===============================
    std::string toFileString() const;
    static Professor fromFileString(const std::string& line);
};
