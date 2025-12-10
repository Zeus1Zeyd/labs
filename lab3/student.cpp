#include "student.h"
#include <iostream>
#include <sstream>

Student::Student(const std::string& studentName) : name(studentName) {}

Student::Student(const std::string& studentName, const std::vector<int>& studentGrades) : 
    name(studentName), grades(studentGrades) {}

std::string Student::getName() const {
    return name;
}

std::vector<int> Student::getGrades() const {
    return grades;
}

void Student::setName(const std::string& newName) {
    name = newName;
}

void Student::setGrades(const std::vector<int>& newGrades) {
    grades = newGrades;
}

void Student::addGrade(int grade) {
    grades.push_back(grade);
}

std::string Student::toString() const {
    std::ostringstream oss;
    oss << name << ": [";
    
    for (size_t i = 0; i < grades.size(); ++i) {
        oss << grades[i];
        if (i < grades.size() - 1) {
            oss << ", ";
        }
    }
    
    oss << "]";
    return oss.str();
}

void Student::print() const {
    std::cout << toString() << std::endl;
}