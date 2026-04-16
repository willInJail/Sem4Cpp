#include "Teacher.h"
#include <iostream>

void Teacher::addLetter(QuadraticEquation eq, std::vector<double> sol, Student* st) {
    Letter letter;
    letter.equation = eq;
    letter.solution = sol;
    letter.student = st;
    queue.push_back(letter);
}

void Teacher::checkAllLetters() {
    table.clear();

    for (size_t i = 0; i < queue.size(); i++) {
        std::string name = queue[i].student->getName();
        bool correct = queue[i].equation.checkSolution(queue[i].solution);

        bool found = false;
        for (size_t j = 0; j < table.size(); j++) {
            if (table[j].first == name) {
                if (correct) table[j].second++;
                found = true;
                break;
            }
        }

        if (!found) {
            table.push_back(std::make_pair(name, correct ? 1 : 0));
        }
    }
}

void Teacher::publishTable() {
    std::cout << "\n=== Accuracy table ===\n";
    std::cout << "Name\tProblems solved\n";
    std::cout << "----------------------------\n";
    for (size_t i = 0; i < table.size(); i++) {
        std::cout << table[i].first << "\t\t" << table[i].second << std::endl;
    }
    std::cout << "============================\n";
}