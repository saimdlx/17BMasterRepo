Sample Homework Markdown
// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: (Leave blank for user)
// ================================================================
// Program Description:
// Student Records Display
// - Demonstrates usage of the Student class.
// - Creates Student objects, sets data using constructors and mutators,
// and displays the student records.
// ================================================================
#include "Student.h"
using namespace std;
// ================================================================
// Main Function:
// - Creates and displays student objects.
// - Uses both default and parameterized constructors.
// - Updates a student's information using setter functions.
// ================================================================
int main() {
// ================================================================
// Student #1:
// - Created using the default constructor.
// - Initially displays default-initialized values.
// ================================================================
cout << "Here is student #1:\n";
Student s1;
s1.displayRecord();
// ================================================================
// Student #2:
// - Created using the parameterized constructor.
// - Displays initialized values (ID, name, units).
// ================================================================
cout << "\nHere is student #2: ";
Student s2(100, "Tom P. Lee", 12);
s2.displayRecord();
// ================================================================
// Updating Student #1:
// - Uses setter functions to update ID, name, and units.
// - Displays the updated record.
// ================================================================
cout << "\nHere is student #1 after the set functions:\n";
s1.setID(101);
s1.setName("John Lee Hooker");
s1.setUnits(15);
s1.displayRecord();
return 0; // End of Program
}
//==============OUTPUT=============================
//Here is student #1:
//
//ID: 0
//
//Name :
//
// Units : 0
//
// Here is student #2:
//ID: 100
//
//Name : Tom P.Lee
//
//Units : 12
//
//Here is student #1 after the set functions :
//
//ID: 101
//
//Name : John Lee Hooker
//
//Units : 15
//
//C : \Users\kevin\source\repos\HW_8\x64\Debug\HW_8.exe(process 4780)
//Press any key to close this window . . .
// ================================================================
// File: Student Class Definition
// - Defines the Student class with member variables and functions.
// - Encapsulates student information including ID, name, and units.
// ================================================================
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
// ================================================================
// Class: Student
// - Represents a student with the following attributes:
// - id: Student's unique identifier.
// - name: Student's full name.
// - units: Number of academic units the student is enrolled in.
// ================================================================
class Student {
private:
int id; // Student ID number
string name; // Student name
int units; // Number of enrolled units
public:
// ================================================================
// Constructors:
// - Student(): Default constructor that initializes members.
// - Student(int, const string&, int): Parameterized constructor to
// initialize all data members.
// ================================================================
Student();
Student(int, const string&, int);
// ================================================================
// Mutator Functions:
// - setID(int): Sets the student's ID.
// - setName(const string&): Sets the student's name.
// - setUnits(int): Sets the number of enrolled units.
// ================================================================
void setID(int);
void setName(const string&);
void setUnits(int);
// ================================================================
// Function: displayRecord
// - Displays the student's complete record including ID, name, and units.
// ================================================================
void displayRecord() const;
};
// ================================================================
// Class: UnderGrad (Derived from Student)
// - Represents an undergraduate student.
// - Adds class level information (e.g., Freshman, Sophomore, etc.).
// - Inherits from the Student class.
// ================================================================
class UnderGrad : public Student {
private:
string classLevel; // Undergraduate class level
public:
// ================================================================
// Constructor: UnderGrad
// - Initializes the undergraduate student with ID, units, name, and class
level.
// - Parameters:
// - int: Student ID
// - int: Units
// - string: Name
// - string: Class level
// ================================================================
UnderGrad(int, int, const string&, const string&);
// ================================================================
// Function: displayRecord
// - Displays the undergraduate student's information including class level.
// ================================================================
void displayRecord() const;
};
// ================================================================
// Class: Grad (Derived from Student)
// - Represents a graduate student.
// - Adds degree information (e.g., MS, PhD).
// - Inherits from the Student class.
// ================================================================
class Grad : public Student {
private:
string degree; // Graduate degree program
public:
// ================================================================
// Constructor: Grad
// - Initializes the graduate student with ID, units, name, and degree.
// - Parameters:
// - int: Student ID
// - int: Units
// - string: Name
// - string: Degree
// ================================================================
Grad(int, int, const string&, const string&);
// ================================================================
// Function: setUnits
// - Overrides the base class function to allow modification of units.
// ================================================================
void setUnits(int); // Override to allow change
// ================================================================
// Function: displayRecord
// - Displays the graduate student’s information including degree.
// ================================================================
void displayRecord() const;
};
#include "Student.h"
// ================================================================
// Constructor: Student
// - Default constructor that initializes:
// - id to 0
// - name to an empty string
// - units to 0
// ================================================================
Student::Student() : id(0), name(" "), units(0) {}
// ================================================================
// Constructor: Student (Overloaded)
// - Initializes the student with provided values for:
// - id, name, and units
// - Parameters:
// - id (int): Student's ID
// - name (string): Student's full name
// - units (int): Number of enrolled units
// ================================================================
Student::Student(int id, const string& name, int units)
{
this->id = id;
this->name = name;
this->units = units;
}
// ================================================================
// Function: setID
// - Sets the student's ID number.
// - Parameters:
// - id (int): New student ID
// ================================================================
void Student::setID(int id)
{
this->id = id;
}
// ================================================================
// Function: setName
// - Sets the student's name.
// - Parameters:
// - name (string): New student name
// ================================================================
void Student::setName(const string& name)
{
this->name = name;
}
// ================================================================
// Function: setUnits
// - Sets the number of units the student is enrolled in.
// - Parameters:
// - units (int): New unit count
// ================================================================
void Student::setUnits(int units)
{
this->units = units;
}
// ================================================================
// Function: displayRecord
// - Displays the student's ID, name, and units.
// - Output format:
// ID: [value]
// Name: [value]
// Units: [value]
// ================================================================
void Student::displayRecord() const
{
cout << "\nID: " << id << endl;
cout << "\nName: " << name << endl;
cout << "\nUnits: " << units << endl;
}
// ================================================================
// Constructor: UnderGrad
// - Initializes an UnderGrad object using the base Student constructor
// and sets the class level (e.g., Freshman, Sophomore).
// - Parameters:
// - id (int): Student ID
// - units (int): Number of enrolled units
// - name (string): Student name
// - classLevel (string): Undergraduate class level
// ================================================================
UnderGrad::UnderGrad(int id, int units, const string& name, const string&
classLevel)
: Student(id, name, units), classLevel(classLevel) {
}
// ================================================================
// Function: UnderGrad::displayRecord
// - Displays basic student information by calling Student::displayRecord()
// and also shows the undergraduate class level.
// ================================================================
void UnderGrad::displayRecord() const
{
Student::displayRecord();
cout << "\nClass: " << classLevel << endl;
}
// ================================================================
// Constructor: Grad
// - Initializes a Grad object using the base Student constructor
// and sets the graduate degree (e.g., MS, PHD).
// - Parameters:
// - id (int): Student ID
// - units (int): Number of enrolled units
// - name (string): Student name
// - degree (string): Graduate degree
// ================================================================
Grad::Grad(int id, int units, const string& name, const string& degree)
: Student(id, name, units), degree(degree) {
}
// ================================================================
// Function: Grad::setUnits
// - Overrides the base class setUnits function to allow modification
// of the number of units for graduate students.
// - Parameters:
// - units (int): Updated unit count
// ================================================================
void Grad::setUnits(int units) {
Student::setUnits(units);
}
// ================================================================
// Function: Grad::displayRecord
// - Displays basic student info and the graduate degree by calling
// the base displayRecord function and appending degree information.
// ================================================================
void Grad::displayRecord() const
{
Student::displayRecord();
cout << "\nDegree: " << degree << endl;
}