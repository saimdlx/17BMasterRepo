// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: Homework 5 - Exception Propagation and Rethrowing
// ================================================================
// Program Description:
// Exception Handling and Data Validation
// - Demonstrates the use of try, catch, and throw for error handling.
// - Validates integer input from the user via standard input.
// - Exception re-throwing and intermediate logging within 
//   a call stack.
// ================================================================
#include <iostream>
using namespace std;
// ================================================================
// Function Prototypes:
// - readData(): Prompts for user input and validates integer type.
// - processData(): Orchestrates data reading and handles re-throws.
// ================================================================
void readData();
void processData();
// ================================================================
// Main Function:
// - Serves as the entry point for program execution.
// - Calls processData() within a top-level try-catch block to
//   handle any uncaught exceptions.
// ================================================================
int main() {
    try {
        processData();
    }
    catch(const exception& e){
        // ================================================================
        // Global Catch Block:
        // - Catches standard exceptions to prevent program crashes.
        // - Displays the error message to the user.
        // ================================================================
        cout << "Error in main: " << e.what() << endl;
    }
    return 0;
}
// ================================================================
// Function: readData
// - Prompts the user to enter an integer value.
// - Validates the input stream; if the input is non-numeric, a
//   std::invalid_argument exception is thrown.
// ================================================================
void readData(){
    int userInput = 0;
    cout << "Enter an integer: ";
    cin >> userInput;
    
    if(cin.fail()){
        throw std::invalid_argument("Invalid integer input");
    }
    else{
        cout << "Input is an integer." << endl;
    }
}
// ================================================================
// Function: processData
// - Calls readData() to retrieve user information.
// - Uses a try-catch block to log error details locally before
//   re-throwing the exception to the caller.
// ================================================================
void processData(){
    try{
        readData();
    }
    catch(const std::invalid_argument& e){
        // ================================================================
        // Local Error Logging:
        // - Outputs a diagnostic message to standard error.
        // - Re-throws the exception to maintain error propagation.
        // ================================================================
        cerr << "[processData] Logging error before rethrow" << endl;
        throw;
    }
}
/*
Program Output using Assignment Input
PS C:\Users\lucky\17BMasterRepo\17BMasterFile\Homework #5\Homework5A> ./a.exe
Enter an integer: abc
[processData] Logging error before rethrow
Error in main: Invalid integer input

Program Output using custom input
PS C:\Users\lucky\17BMasterRepo\17BMasterFile\Homework #5\Homework5A> ./a.exe
Enter an integer: 5
Input is an integer.
*/