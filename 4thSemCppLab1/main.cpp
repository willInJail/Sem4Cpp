#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "QuadraticEquation.h"
#include "Student.h"
#include "Teacher.h"

using namespace std;

vector<QuadraticEquation> readEquationsFromFile(string filename) {
    vector<QuadraticEquation> equations;
    ifstream file(filename.c_str());

    if (!file.is_open()) {
        cout << "OpenFileError: " << filename << endl;
        return equations;
    }

    double a, b, c;
    while (file >> a >> b >> c) {
        equations.push_back(QuadraticEquation(a, b, c));
    }

    file.close();
    return equations;
}

int main() {
    srand((unsigned int)time(0));

    vector<QuadraticEquation> equations = readEquationsFromFile("equations.txt");

    if (equations.empty()) {
        cout << "File equations.txt is empty" << endl;
        cout << "Create a file with equations in the format: a b c" << endl;
    }

    vector<Student*> students;
    students.push_back(new GoodStudent("Fedor1"));
    students.push_back(new AverageStudent("Fedor2"));
    students.push_back(new BadStudent("Genadiy"));
    students.push_back(new GoodStudent("Oleg"));
    students.push_back(new AverageStudent("Olga"));

    Teacher teacher;

    for (size_t i = 0; i < equations.size(); i++) {
        for (size_t j = 0; j < students.size(); j++) {
            vector<double> solution = students[j]->solveEquation(equations[i]);
            teacher.addLetter(equations[i], solution, students[j]);
        }
    }

    teacher.checkAllLetters();
    teacher.publishTable();

    for (size_t i = 0; i < students.size(); i++) {
        delete students[i];
    }

    return 0;
}