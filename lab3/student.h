#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student {
private:
    std::string name;
    std::vector<int> grades;
    
public:
    Student(const std::string& studentName);
    Student(const std::string& studentName, const std::vector<int>& studentGrades);
    
    std::string getName() const;
    std::vector<int> getGrades() const;
    
    void setName(const std::string& newName);
    void setGrades(const std::vector<int>& newGrades);
    
    void addGrade(int grade);
    
    std::string toString() const;
    void print() const;
};

#endif