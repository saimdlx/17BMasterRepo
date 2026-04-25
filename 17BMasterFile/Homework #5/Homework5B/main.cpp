// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: Homework 5 - RAII and Stack Unwinding
// ================================================================
// Program Description:
// Resource Management and Exception Handling
// - Demonstrates RAII (Resource Acquisition Is Initialization) pattern.
// - Shows stack unwinding mechanism.
// - Illustrates automatic destructor invocation when exceptions occurs.
// ================================================================
#include <iostream>
#include <stdexcept>
using namespace std;
// ================================================================
// Class: ResourceTracker
// - Tracks resource acquisition and release through lifecycle.
// - Prints messages in constructor and destructor for visibility.
// ================================================================
class ResourceTracker {
    public:
    // ================================================================
    // Constructor: ResourceTracker
    // - Called upon object creation.
    // - Signals resource acquisition.
    // ================================================================
    ResourceTracker(){
        cout << "Resource acquired" << endl;
    }
    // ================================================================
    // Destructor: ~ResourceTracker
    // - Called upon object destruction (stack unwinding or end of scope).
    // - Signals resource release.
    // ================================================================
    ~ResourceTracker(){
        cout << "Resource released" << endl;
    }
};

// ================================================================
// Function: dangerousFunction
// - Creates a local ResourceTracker object.
// - Throws a runtime_error to trigger stack unwinding.
// ================================================================
void dangerousFunction() {
    ResourceTracker sample;
    throw std::runtime_error("Runtime error occured");
}
// ================================================================
// Main Function:
// - Entry point of program.
// - Executes code within try block to handle potential exceptions.
// - Catches and displays exception details.
// ================================================================
int main(){
    try{
        // ================================================================
        // Execute Dangerous Logic:
        // - Calls function that is guaranteed to throw an exception.
        // ================================================================
        dangerousFunction();
    }
    catch(const exception& e){
        // ================================================================
        // Exception Handling:
        // - Catches standard exceptions by reference.
        // - Outputs error message from exception object.
        // ================================================================
        cout << "Caught exception: " << e.what() << endl;
    }
    return 0; // End of Program
}
/*
Program Output:
PS C:\Users\lucky\17BMasterRepo\17BMasterFile\Homework #5\Homework5B> ./a.exe
Resource acquired
Resource released
Caught exception: Runtime error occured
*/
