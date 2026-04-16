#include "QuadraticEquation.h"
#include <cmath>

QuadraticEquation::QuadraticEquation() : a(0), b(0), c(0) {}

QuadraticEquation::QuadraticEquation(double a_, double b_, double c_)
    : a(a_), b(b_), c(c_) {}

std::vector<double> QuadraticEquation::solve() {
    std::vector<double> roots;

    if (fabs(a) < 1e-9) {
        if (fabs(b) > 1e-9) {
            roots.push_back(-c / b);
        }
        return roots;
    }

    double D = b * b - 4 * a * c;

    if (D < -1e-9) {
        return roots;
    }
    else if (fabs(D) < 1e-9) {
        roots.push_back(-b / (2 * a));
    }
    else {
        roots.push_back((-b - sqrt(D)) / (2 * a));
        roots.push_back((-b + sqrt(D)) / (2 * a));
    }
    return roots;
}

bool QuadraticEquation::checkSolution(std::vector<double>& proposed) {
    std::vector<double> correct = solve();
    if (correct.size() != proposed.size()) return false;
    for (size_t i = 0; i < correct.size(); i++) {
        if (fabs(correct[i] - proposed[i]) > 1e-6) return false;
    }
    return true;
}