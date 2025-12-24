#pragma once
// FileManager.h
// Handles all file operations (Read / Write / Update / Delete / Log)

#pragma once
#include <vector>
#include <string>
#include "Student.h"
#include "Course.h"
#include "Professor.h"

class FileManager {
private:
    const std::string basePath = "D:\\";

    const std::string studentsFile = basePath + "students.txt";
    const std::string coursesFile = basePath + "courses.txt";
    const std::string professorsFile = basePath + "professors.txt";
    const std::string logFile = basePath + "system_log.txt";

public:
    // ===============================
    // STUDENTS
    // ===============================
    std::vector<Student> loadStudents();
    void saveStudents(const std::vector<Student>& students);

    // ===============================
    // COURSES
    // ===============================
    std::vector<Course> loadCourses();
    void saveCourses(const std::vector<Course>& courses);

    // ===============================
    // PROFESSORS
    // ===============================
    std::vector<Professor> loadProfessors();
    void saveProfessors(const std::vector<Professor>& professors);

    // ===============================
    // DELETE OPERATIONS
    // ===============================
    void deleteStudentById(const std::string& id);
    void deleteCourseByCode(const std::string& code);
    void deleteProfessorById(const std::string& id);

    // ===============================
    // LOGGING
    // ===============================
    void logAction(const std::string& action);
};
