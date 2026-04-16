#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "QuadraticEquation.h"

class Student {
protected:
    std::string name;

public:
    Student(std::string name_);
    virtual ~Student();
    virtual std::vector<double> solveEquation(QuadraticEquation& eq) = 0;
    std::string getName();
};

class GoodStudent : public Student {
public:
    GoodStudent(std::string name_);
    std::vector<double> solveEquation(QuadraticEquation& eq);
};

class AverageStudent : public Student {
public:
    AverageStudent(std::string name_);
    std::vector<double> solveEquation(QuadraticEquation& eq);
};

class BadStudent : public Student {
public:
    BadStudent(std::string name_);
    std::vector<double> solveEquation(QuadraticEquation& eq);
};

#endif