#pragma once
// Admin.h
// Administration logic (full control)

#pragma once
#include <vector>
#include <string>
#include "Student.h"
#include "Professor.h"
#include "Course.h"
#include "FileManager.h"

class Admin {
private:
    // Demonstrate ARRAY usage (fixed size)
    std::string faculties[4] = {
        "Engineering", "Science", "Business", "Arts"
    };

    std::string departments[6] = {
        "Computer Science", "Electrical", "Mechanical",
        "Accounting", "English", "Biology"
    };

public:
    // ===============================
    // STUDENT MANAGEMENT (CRUD)
    // ===============================
    void addStudent(FileManager& fm);
    void updateStudent(FileManager& fm);
    void deleteStudent(FileManager& fm);

    // ===============================
    // PROFESSOR MANAGEMENT
    // ===============================
    void addProfessor(FileManager& fm);
    void assignProfessorToCourse(FileManager& fm);

    // ===============================
    // COURSE MANAGEMENT
    // ===============================
    void addCourse(FileManager& fm);
    void deleteCourse(FileManager& fm);

    // ===============================
    // ACADEMIC STRUCTURE
    // ===============================
    void viewFaculties() const;
    void viewDepartments() const;
    void manageAcademicYears() const;
    void manageAcademicLevels() const;

    // ===============================
    // FEES MANAGEMENT
    // ===============================
    void manageStudentFees(FileManager& fm);
    // ===============================
    // VIEW (PRINT ALL)
    // ===============================
    void viewAllStudents(FileManager& fm);
    void viewAllCourses(FileManager& fm);
    void viewAllProfessors(FileManager& fm);

};
