#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

class Talon {
public:
    string name;
    int score;
    string instructor;
};

class Student {
public:
    string name;
    string group;
    vector<Talon> talons;

    int getTalonCount() {
        return talons.size();
    }
};

int main() {
    // Read data from the file and store it in an array of Student objects
    string path = "C:\\Users\\lissa\\OneDrive\\Робочий стіл\\Talon\\";

    vector<Student> students;
    ifstream input(path + "data.txt");
    string line;

    while (getline(input, line)) {
        Student student;
        student.name = line;
        getline(input, student.group);
        int talonCount;
        input >> talonCount;
        getline(input, line); // Consume the newline character
        for (int i = 0; i < talonCount; i++) {
            Talon talon;
            getline(input, talon.name);
            input >> talon.score;
            getline(input, line); // Consume the newline character
            getline(input, talon.instructor);
            student.talons.push_back(talon);
        }
        students.push_back(student);
    }
    input.close();

    // Find students with more than one talon and write their names to file1.txt
    ofstream output1(path + "file1.txt");
    for (Student student : students) {
        if (student.getTalonCount() > 1) {
            output1 << student.name << " - " << student.group << endl;
        }
    }
    output1.close();

    // Find the instructor with the highest count of talons and write their name to file2.txt
    vector<string> instructors;
    vector<int> talonCounts;
    for (Student student : students) {
        for (Talon talon : student.talons) {
            int index = -1;
            for (int i = 0; i < instructors.size(); i++) {
                if (instructors[i] == talon.instructor) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                instructors.push_back(talon.instructor);
                talonCounts.push_back(talon.score);
            }
            else {
                talonCounts[index] += talon.score;
            }
        }
    }

    int maxCount = 0;
    string maxInstructor;
    for (int i = 0; i < instructors.size(); i++) {
        if (talonCounts[i] > maxCount) {
            maxCount = talonCounts[i];
            maxInstructor = instructors[i];
        }
    }
    ofstream output2(path + "file2.txt");
    output2 << maxInstructor << endl;
    output2.close();

    return 0;
}
