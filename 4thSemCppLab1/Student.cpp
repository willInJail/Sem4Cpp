#include "Student.h"
#include <cstdlib>

Student::Student(std::string name_) : name(name_) {}
Student::~Student() {}

std::string Student::getName() {
    return name;
}

GoodStudent::GoodStudent(std::string name_) : Student(name_) {}

std::vector<double> GoodStudent::solveEquation(QuadraticEquation& eq) {
    return eq.solve();
}

AverageStudent::AverageStudent(std::string name_) : Student(name_) {}

std::vector<double> AverageStudent::solveEquation(QuadraticEquation& eq) {
    std::vector<double> correct = eq.solve();

    if (rand() % 100 < 50) {
        if (correct.size() > 0) {
            correct[0] = -correct[0] + 1;
        }
    }
    return correct;
}

BadStudent::BadStudent(std::string name_) : Student(name_) {}

std::vector<double> BadStudent::solveEquation(QuadraticEquation& eq) {
    std::vector<double> answer;
    answer.push_back(0);
    return answer;
}