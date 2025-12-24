#pragma once
// Student.h
// Defines Student class and CourseGrade structure

#include <string>
#include <vector>
#include <iostream>

// ===============================
// STRUCT: CourseGrade
// ===============================
// Holds grades + attendance for ONE course
struct CourseGrade {
    std::string courseCode;

    // Grades
    double ass1 = 0.0;
    double ass2 = 0.0;
    double cw = 0.0;
    double finalExam = 0.0;

    // Course info
    int outOf = 100;          // 100 or 150
    bool isPractical = false;

    // Attendance
    int attendedLectures = 0;
    int totalLectures = 0;
};

// ===============================
// CLASS: Student
// ===============================
class Student {
private:
    // Basic info
    std::string id;
    std::string name;
    std::string department;

    int academicYear;
    int academicLevel;
    bool tuitionPaid;

    // All courses + grades + attendance
    std::vector<CourseGrade> grades;

public:
    // ===============================
    // Constructors
    // ===============================
    Student();
    Student(const std::string& _id, const std::string& _name);

    // ===============================
    // Getters
    // ===============================
    std::string getId() const;
    std::string getName() const;
    std::string getDepartment() const;
    int getAcademicYear() const;
    int getAcademicLevel() const;
    bool isTuitionPaid() const;

    // ===============================
    // Setters (USED FOR UPDATE)
    // ===============================
    void setName(const std::string& n);
    void setDepartment(const std::string& d);
    void setAcademicYear(int y);
    void setAcademicLevel(int l);
    void setTuitionPaid(bool paid);

    // ===============================
    // Views (Student Role)
    // ===============================
    void viewPersonalData() const;
    void viewGrades() const;
    void viewGPA() const;
    void viewTuitionStatus() const;

    // ===============================
    // Grades & Attendance Logic
    // ===============================
    CourseGrade* findCourseGrade(const std::string& courseCode); // pointer usage
    void addOrUpdateGrade(const CourseGrade& g);

    double calculateCoursePercentage(const CourseGrade& g) const;
    std::string evaluateGrade(double percent) const;

    // ===============================
    // File Handling
    // ===============================
    std::string toFileString() const;
    static Student fromFileString(const std::string& line);
};
