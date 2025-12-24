#pragma once
// Course.h
// Defines Course class

#include <string>
#include <iostream>

class Course {
private:
    std::string code;     // Course code (e.g. CS101)
    std::string name;     // Course name
    bool practical;       // Practical or theoretical
    int outOf;            // Total marks (100 or 150)

public:
    // ===============================
    // Constructors
    // ===============================
    Course();
    Course(const std::string& c,
        const std::string& n,
        bool isPractical,
        int out);

    // ===============================
    // Getters (IMPORTANT)
    // ===============================
    std::string getCode() const;
    std::string getName() const;
    bool isPractical() const;
    int getOutOf() const;

    // ===============================
    // Utility / View
    // ===============================
    void printCourseInfo() const;

    // ===============================
    // File Handling
    // ===============================
    std::string toFileString() const;
    static Course fromFileString(const std::string& line);
};
