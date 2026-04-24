// ================================================================
// Programmer: Saim Ahmed
// Class: CS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: FeetInches Class Header File
// ================================================================
// Program Description:
// - Defines the FeetInches class with member variables and functions.
// - Handles distance measurements in feet and inches.
// - Includes logic for simplifying inch values into feet.
// ================================================================
#ifndef FEETINCHES_H
#define FEETINCHES_H

#include <iostream>
using namespace std;

// ================================================================
// Class: FeetInches
// - Represents a measurement in feet and inches.
// - feet: The feet component of the measurement.
// - inches: The inches component of the measurement.
// ================================================================
class FeetInches{
    private:
        int feet;   // Number of feet
        int inches; // Number of inches
        // ================================================================
        // Function: simplify
        // - Corrects the feet and inches so that inches < 12.
        // ================================================================
        void simplify();
    public:
        // ================================================================
        // Constructors:
        // - FeetInches(int, int): Parameterized constructor with defaults.
        // - ~FeetInches(): Destructor.
        // ================================================================
        FeetInches(int feet = 0, int inches = 0);
        ~FeetInches();

        // ================================================================
        // Operator Overloads:
        // - operator+: Adds two FeetInches objects.
        // - operator-: Subtracts two FeetInches objects.
        // - operator++: Prefix and postfix increment (placeholders).
        // - operator<, >, ==: Relational comparisons.
        // ================================================================
        FeetInches operator+(const FeetInches&);
        FeetInches operator-(const FeetInches&);

        void operator++();
        void operator++(int);

        bool operator<(FeetInches&);
        bool operator>(FeetInches&);
        bool operator==(FeetInches&);
        
        // ================================================================
        // Friend Functions:
        // - operator<<: Overloaded output stream operator.
        // - operator>>: Overloaded input stream operator.
        // ================================================================
        friend ostream &operator<<(ostream&, FeetInches&);
        friend istream &operator>>(istream&, FeetInches&);

};

#endif
