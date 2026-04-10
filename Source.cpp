#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class QuadraticEquation {
private:
    double a, b, c;

public:
    QuadraticEquation() : a(0), b(0), c(0) {}
    QuadraticEquation(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}

    vector<double> solve() {
        vector<double> roots;

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

    bool checkSolution(vector<double>& proposed) {
        vector<double> correct = solve();
        if (correct.size() != proposed.size()) return false;
        for (size_t i = 0; i < correct.size(); i++) {
            if (fabs(correct[i] - proposed[i]) > 1e-6) return false;
        }
        return true;
    }
};

class Student {
protected:
    string name;

public:
    Student(string name_) : name(name_) {}
    virtual ~Student() {}
    virtual vector<double> solveEquation(QuadraticEquation& eq) = 0;

    string getName() { return name; }

};


class GoodStudent : public Student {
public:
    GoodStudent(string name_) : Student(name_) {}

    vector<double> solveEquation(QuadraticEquation& eq) {
        return eq.solve();
    }

};

class AverageStudent : public Student {
public:
    AverageStudent(string name_) : Student(name_) {}

    vector<double> solveEquation(QuadraticEquation& eq) {
        vector<double> correct = eq.solve();

        // 50% 
        if (rand() % 100 < 50) {
            if (correct.size() > 0) {
                correct[0] = -correct[0] + 1;
            }
        }
        return correct;
    }
};

class BadStudent : public Student {
public:
    BadStudent(string name_) : Student(name_) {}

    vector<double> solveEquation(QuadraticEquation& eq) {
        vector<double> answer;
        answer.push_back(0);
        return answer;
    }

};

struct Letter {
    QuadraticEquation equation;
    vector<double> solution;
    Student* student;
};

class Teacher {
private:
    vector<Letter> queue;
    vector<pair<string, int>> table;

public:
    void addLetter(QuadraticEquation eq, vector<double> sol, Student* st) {
        Letter letter;
        letter.equation = eq;
        letter.solution = sol;
        letter.student = st;
        queue.push_back(letter);
    }

    void checkAllLetters() {
        table.clear();

        for (size_t i = 0; i < queue.size(); i++) {
            string name = queue[i].student->getName();
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
                table.push_back(make_pair(name, correct ? 1 : 0));
            }
        }
    }

    void publishTable() {
        cout << "\n=== Accuracy table ===\n";
        cout << "Name\tProblems solved\n";
        cout << "----------------------------\n";
        for (size_t i = 0; i < table.size(); i++) {
            cout << table[i].first << "\t\t" << table[i].second << endl;
        }
        cout << "============================\n";
    }
};


vector<QuadraticEquation> readEquationsFromFile(string filename) {
    vector<QuadraticEquation> equations;
    ifstream file(filename.c_str());

    if (!file.is_open()) {
        cout << "OpenFileError" << filename << endl;
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
    srand(time(0));

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