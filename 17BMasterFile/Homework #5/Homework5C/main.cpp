// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: Homework 5 - Custom Exception Hierarchy
// ================================================================
// Program Description:
// Creates a hierarchy of file-related exception classes:
// - FileException (Base)
// - FileNotFoundException (Derived)
// - PermissionDeniedException (Derived)
// Simulates an operation that may throw
// exceptions and demonstrates how to catch them using structured
// try-catch blocks.
// ================================================================
#include <iostream>
#include <exception>
#include <string>
using namespace std;
// ================================================================
// Class: FileException (Derived from std::exception)
// - Serves as the base class for file-related exceptions.
// - Overrides the what() function to provide a generic error message.
// ================================================================
class FileException : public std::exception {
    public:
    virtual const char* what() const noexcept override {
        return "File exception occurred";
    }
};

// ================================================================
// Class: FileNotFoundException (Derived from FileException)
// - Represents an error where a requested file cannot be found.
// - Overrides what() to provide a specific "File not found" message.
// ================================================================
class FileNotFoundException : public FileException {
    public:
    const char* what() const noexcept override {
        return "File not found";
    }
};

// ================================================================
// Class: PermissionDeniedException (Derived from FileException)
// - Represents an error where file access is denied.
// - Overrides what() to provide a specific "Permission denied" message.
// ================================================================
class PermissionDeniedException : public FileException {
    public:
    const char* what() const noexcept override {
        return "Permission denied";
    }
};

// ================================================================
// Function: openFile
// - Simulates opening a file and throwing exceptions based on a code.
// - Parameters:
//   - code (int): Error code to simulate:
//     - 1: Throws FileNotFoundException
//     - 2: Throws PermissionDeniedException
// ================================================================
void openFile(int code) {
    if (code == 1) {
        throw FileNotFoundException();
    } else if (code == 2) {
        throw PermissionDeniedException();
    }
}
// ================================================================
// Main Function:
// - Demonstrates exception handling using try and catch blocks.
// - Calls openFile() and catches specific and base exceptions to
//   show catch block ordering and exception polymorphism.
// ================================================================
int main() {
    // ================================================================
    // Exception Handling Block:
    // - Attempts to open a file with sample input code 1.
    // - Catches exceptions in order from most specific to most general.
    // ================================================================
    try {
        openFile(1);
    } 
    catch (const FileNotFoundException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    } 
    catch (const PermissionDeniedException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    } 
    catch (const FileException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    } 
    return 0; // End of Program
}

/*
Program Output Using Assignment Input:
Code = 1
PS C:\Users\lucky\17BMasterRepo\17BMasterFile\Homework #5\Homework5C> ./a.exe
Error: File not found

Code = 2
PS C:\Users\lucky\17BMasterRepo\17BMasterFile\Homework #5\Homework5C> ./a.exe
Error: Permission denied
*/