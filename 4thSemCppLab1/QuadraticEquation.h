#pragma once
#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

#include <vector>

class QuadraticEquation {
private:
    double a, b, c;

public:
    QuadraticEquation();
    QuadraticEquation(double a_, double b_, double c_);
    std::vector<double> solve();
    bool checkSolution(std::vector<double>& proposed);
};

#endif