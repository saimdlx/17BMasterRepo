/* 
 * File:   main.cpp
 * Author: Saim Ahmed
 * Created on: February 25, 2026
 * Purpose:  Student Course Registration System
 */

//System Libraries Here
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Global Variables

//Function Prototypes Here
enum Major{
    CS,
    ENGINEERING,
    MATH,
    PHYSICS
};

struct Student{
    int id;
    string name;
    Major major;
    double gpa;
};

typedef Student* StudentPtr;

void displayMenu();
StudentPtr createStudent();
void addStudent(vector<StudentPtr>& students);
void displayStudents(const vector<StudentPtr>& students);
string majorToString(Major m);
void deleteAll(vector<StudentPtr>& students);

//Program Execution Begins Here
int main() {
    vector<StudentPtr> students;
    /*
    int choice = 0;
    while (choice != 3){
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            break;
        case 2:
            break;
        default:
            break;
        }
    }
    */
    addStudent(students);
    cout << students[0]->name << " " << students[0]->id << " " << students[0]->gpa << endl;
    deleteAll(students);
    cout << students[0]->gpa << endl;
    return 0;
}

void displayMenu(){

    cout << "===== Student Registration System =====" << '\n';
    cout << "1. Add Student" << '\n';
    cout << "2. Display All Students" << '\n';
    cout << "3. Exit" << '\n';
    cout << "Enter choice: ";
}

StudentPtr createStudent(){
    int id = 0;
    string name = "";
    double gpa = 0;
    //In other words, Student* p1 = new Student.
    //StudentPtr is just a typedef alias!
    //Add "Add Student" questions here to be returned with the pointer object.
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter GPA: ";
    cin >> gpa;
    StudentPtr p1 = new Student;
    p1->id = id;
    p1->name = name;
    p1->gpa = gpa;
    return p1;
}

void addStudent(vector<StudentPtr>& students){
    //Given a reference vector, add a student to the vector list.
    StudentPtr newStu = createStudent();
    students.push_back(newStu);
}

/*
string majorToString (Major m){

}
*/


void deleteAll(vector<StudentPtr>& students){
    //Since we're working with dynamically allocated memory, we need to deallocate the pointers.
    for (StudentPtr std : students){
        delete std;
    }
}