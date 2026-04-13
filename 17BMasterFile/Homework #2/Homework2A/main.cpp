#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum Major
{
    CS = 1,
    ENGINEERING = 2,
    MATH = 3,
    PHYSICS = 4
};

struct Student
{
    int id;
    string name;
    Major major;
    double gpa;
};

typedef Student *StudentPtr;

void displayMenu();
StudentPtr createStudent();
void addStudent(vector<StudentPtr> &students);
void displayStudents(const vector<StudentPtr> &students);
string majorToString(Major m);
void deleteAll(vector<StudentPtr> &students);

int main()
{
    vector<StudentPtr> students;

    int choice = 0;
    while (choice < 4)
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent(students);
            break;
        case 2:
            displayStudents(students);
            break;
        case 3:
            cout << "Goodbye!";
            deleteAll(students);
            break;
        }
    }
    return 0;
}

void displayMenu()
{
    cout << "===== Student Registration System =====" << '\n';
    cout << "1. Add Student" << '\n';
    cout << "2. Display All Students" << '\n';
    cout << "3. Exit" << '\n';
    cout << "Enter choice: ";
}

StudentPtr createStudent()
{

    int id = 0;
    string name = "";
    int majorMarker = 0;
    Major m;
    double gpa = 0;

    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter name: ";
    cin >> name;
    cout << "Select Major: " << '\n';
    cout << "1. CS" << '\n';
    cout << "2. ENGINEERING" << '\n';
    cout << "3. MATH" << '\n';
    cout << "4. PHYSICS" << '\n';
    cout << "Enter choice: ";
    cin >> majorMarker;
    m = static_cast<Major>(majorMarker);
    cout << "Enter GPA: ";
    cin >> gpa;

    StudentPtr freshStudent = new Student;
    freshStudent->id = id;
    freshStudent->name = name;
    freshStudent->gpa = gpa;
    freshStudent->major = m;

    return freshStudent;
}

void addStudent(vector<StudentPtr> &students)
{
    cout << endl;
    StudentPtr newStu = createStudent();
    students.push_back(newStu);
    cout << "Student Added Successfully!" << '\n';
    cout << endl;
}

void displayStudents(const vector<StudentPtr> &students)
{
    for (int i = 0; i < students.size(); i++)
    {
        cout << endl;
        cout << "ID: " << students[i]->id << '\n';
        cout << "Name: " << students[i]->name << '\n';
        cout << "Major: " << majorToString(students[i]->major) << '\n';
        cout << "GPA: " << students[i]->gpa << '\n';
        cout << "-----------------------" << '\n';
        cout << endl;
    }
}

string majorToString(Major m)
{
    string result;
    switch (m)
    {
    case 1:
        result = "Computer Science";
        break;
    case 2:
        result = "Engineering";
        break;
    case 3:
        result = "Math";
        break;
    case 4:
        result = "Physics";
        break;
    }
    return result;
}

void deleteAll(vector<StudentPtr> &students)
{
    for (StudentPtr std : students)
    {
        delete std;
    }
    students.clear();
}
