// ================================================= ================ 
// Programmer: Saim Ahmed
// Class: CIS-17B
// Instructor: Med Mogasemi
//
// ================================================= ================ 
// Program: Student Course Registration System
// ================================================= ================ 
// Program Description:
// This program allows for the management of student records.
// - It allows adding new students with their ID, name, major, and GPA.
// - It can display a list of all students currently in the system.
// - It handles dynamic memory allocation for student objects.
// ================================================= ================ 

// System Libraries Here
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ================================================= ================ 
// Enum: Major
// - Represents the different majors a student can enroll in.
// ================================================= ================ 
enum Major
{
    CS = 1,
    ENGINEERING = 2,
    MATH = 3,
    PHYSICS = 4
};

// ================================================= ================ 
// Struct: Student
// - Represents a student with the following attributes:
// - id: Student's unique identifier.
// - name: Student's full name.
// - major: The student's chosen major from the Major enum.
// - gpa: The student's Grade Point Average.
// ================================================= ================ 
struct Student
{
    int id;
    string name;
    Major major;
    double gpa;
};

// ================================================= ================ 
// Type Definition: StudentPtr
// - Defines a pointer to a Student object for easier use with
//   dynamic memory allocation.
// ================================================= ================ 
typedef Student *StudentPtr;

// Function Prototypes Here
void displayMenu();
StudentPtr createStudent();
void addStudent(vector<StudentPtr> &students);
void displayStudents(const vector<StudentPtr> &students);
string majorToString(Major m);
void deleteAll(vector<StudentPtr> &students);

// ================================================= ================ 
// Main Function:
// - Drives the program by displaying a menu and handling user choices.
// - Manages a vector of student pointers.
// - Loops until the user chooses to exit.
// ================================================= ================ 
int main()
{
    vector<StudentPtr> students; // Holds all student instances

    int choice = 0;
    while (choice < 4) // Loop until exit choice
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            // ================================================= ================ 
            // Add Student:
            // - Calls the function to add a new student to the vector.
            // ================================================= ================ 
            addStudent(students);
            break;
        case 2:
            // ================================================= ================ 
            // Display Students:
            // - Calls the function to display all student records.
            // ================================================= ================ 
            displayStudents(students);
            break;
        case 3:
            // ================================================= ================ 
            // Exit:
            // - Displays a goodbye message.
            // - Deallocates all dynamically created student objects.
            // - Exits the program.
            // ================================================= ================ 
            cout << "Goodbye!";
            deleteAll(students);
            return 0;
            break;
        }
    }
    return 0; // End of Program
}

// ================================================= ================ 
// Function: displayMenu
// - Displays the main menu options to the user.
// ================================================= ================ 
void displayMenu()
{
    cout << "===== Student Registration System =====" << '\n';
    cout << "1. Add Student" << '\n';
    cout << "2. Display All Students" << '\n';
    cout << "3. Exit" << '\n';
    cout << "Enter choice: ";
}

// ================================================= ================ 
// Function: createStudent
// - Prompts the user to enter information for a new student.
// - Dynamically allocates a new Student object.
// - Initializes the object with user-provided data.
// - Returns a pointer to the newly created Student object.
// ================================================= ================ 
StudentPtr createStudent() {

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

    StudentPtr p1 = new Student;
    p1->id = id;
    p1->name = name;
    p1->gpa = gpa;
    p1->major = m;
    return p1;
}

// ================================================= ================ 
// Function: addStudent
// - Orchestrates the addition of a new student.
// - Calls createStudent() to get a new student object.
// - Adds the new student pointer to the main student vector.
// - Parameters:
// - students (vector<StudentPtr>&): A reference to the vector of students.
// ================================================= ================ 
void addStudent(vector<StudentPtr> &students)
{
    cout << endl;
    StudentPtr newStu = createStudent();
    students.push_back(newStu);
    cout << "Student Added Successfully!" << '\n';
    cout << endl;
}

// ================================================= ================ 
// Function: displayStudents
// - Iterates through the vector of students and displays their records.
// - Calls majorToString to convert the major enum to a readable string.
// - Parameters:
// - students (const vector<StudentPtr>&): A const reference to the vector
//   of students to prevent modification.
// ================================================= ================ 
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

// ================================================= ================ 
// Function: majorToString
// - Converts a Major enum value into its corresponding string representation.
// - Parameters:
// - m (Major): The major enum to be converted.
// - Returns:
// - (string): The string name of the major.
// ================================================= ================ 
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

// ================================================= ================ 
// Function: deleteAll
// - Frees all dynamically allocated memory for student objects.
// - Iterates through the vector and deletes each student pointer.
// - Clears the vector to remove all dangling pointers.
// - Parameters:
// - students (vector<StudentPtr>&): A reference to the vector of students.
// ================================================= ================ 
void deleteAll(vector<StudentPtr> &students)
{
    for (StudentPtr std : students)
    {
        delete std;
    }
    students.clear();
}
