// ================================================================
// Programmer: 
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: Homework 5 - Input Validation vs Exception Use
// ================================================================
// Program Description:
// Integer Input Validation and Exception Handling
// - Prompts the user for a positive integer.
// - Validates input and handles invalid data types.
// - Demonstrates exception handling for values exceeding a defined limit.
// ================================================================
#include <iostream>
#include <limits>
#include <string>
using namespace std;
// ================================================================
// Main Function:
// - Orchestrates the user input loop.
// - Performs type validation and range checking.
// - Implements exception handling for out-of-range values.
// ================================================================
int main(){
    int input = 0;
    // ================================================================
    // Input Loop:
    // - Continuously prompts the user until the program is terminated.
    // - Handles invalid inputs by clearing the stream and ignoring bad data.
    // ================================================================
    while (true){
        cout << "Enter a positive integer: ";
        cin >> input;
        if (cin.fail()){
            cout << "Invalid input, try again." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        try{
            // ================================================================
            // Range Validation:
            // - Checks if the input exceeds the maximum allowed value (1,000,000).
            // - Throws an out_of_range exception if the constraint is violated.
            // ================================================================
            if (input > 1000000){
            // ================================================================
            //  The use of exceptions for extreme cases is implemented to signal serious violations
            //  of rules and constraints. Unlike a typo, which is an "expected" user flaw that gets handled
            //  by the loop, a value that exceeds some numerical limit may instead need the program to handle
            //  it using a specific error-handling block compared to just asking the user to try again. 
            //
            //  Exceptions have very high overhead, and should be used for cases where a program cannot
            //  proceed normally in light of some security or constraint violation.
            // ================================================================
                throw std::out_of_range("Value exceeds allowed maximum");
            }
        }
        catch(const exception& e){
            cout << "Error: " << e.what() << endl;
        }
    }
    return 0;
}
/*
Program Output Using Assignment Input
PS C:\Users\lucky\17BMasterRepo\17BMasterFile\Homework #5\Homework5D> ./a.exe
Enter a positive integer: 1
Enter a positive integer: 2
Enter a positive integer: 3
Enter a positive integer: 2000000
Error: Value exceeds allowed maximum
*/