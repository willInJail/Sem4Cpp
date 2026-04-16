#pragma once
#ifndef TEACHER_H
#define TEACHER_H

#include <vector>
#include <string>
#include <utility>
#include "QuadraticEquation.h"
#include "Student.h"

struct Letter {
    QuadraticEquation equation;
    std::vector<double> solution;
    Student* student;
};

class Teacher {
private:
    std::vector<Letter> queue;
    std::vector<std::pair<std::string, int>> table;

public:
    void addLetter(QuadraticEquation eq, std::vector<double> sol, Student* st);
    void checkAllLetters();
    void publishTable();
};

#endif