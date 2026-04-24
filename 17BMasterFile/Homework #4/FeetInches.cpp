// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: FeetInches Class Implementation File
// ================================================================
// Program Description:
// - Implementation of the FeetInches class methods.
// - Provides logic for addition, subtraction, and comparison.
// - Normalizes measurements through the simplify function.
// ================================================================
#include "FeetInches.h"
#include <iostream>
using namespace std;

// ================================================================
// Constructor: FeetInches
// - Initializes the object with feet and inches.
// - Calls simplify() to normalize values.
// - Parameters:
// - feet (int): Initial feet count.
// - inches (int): Initial inches count.
// ================================================================
FeetInches::FeetInches(int feet, int inches) {
    this->feet = feet;
    this->inches = inches;
    this->simplify();
}

// ================================================================
// Destructor: FeetInches
// - Standard destructor for class cleanup.
// ================================================================
FeetInches::~FeetInches(){}

// ================================================================
// Function: simplify
// - Converts total inches into properly formatted feet and inches.
// - Ensures inches remains in the range [0, 11].
// ================================================================
void FeetInches::simplify(){

    int totInches = ((feet * 12) + inches);
    feet = totInches / 12;
    inches = totInches % 12;

}

// ================================================================
// Function: operator+
// - Overloaded addition operator.
// - Adds feet and inches of two objects and simplifies result.
// - Parameters:
// - obj (const FeetInches&): The object to add.
// ================================================================
FeetInches FeetInches::operator+(const FeetInches& obj){
    FeetInches sum((feet + obj.feet), (inches + obj.inches));
    sum.simplify();
    return sum;
}

// ================================================================
// Function: operator-
// - Overloaded subtraction operator.
// - Subtracts feet and inches of two objects and simplifies result.
// - Parameters:
// - obj (const FeetInches&): The object to subtract.
// ================================================================
FeetInches FeetInches::operator-(const FeetInches& obj){
    FeetInches diff((feet - obj.feet), (inches - obj.inches));
    diff.simplify();
    return diff;
}

// ================================================================
// Function: operator<
// - Overloaded less-than comparison.
// - Parameters:
// - obj (FeetInches&): Object to compare against.
// ================================================================
bool FeetInches::operator<(FeetInches& obj){
    int ref = (feet * 12) + inches;
    int obs = (obj.feet * 12) + obj.inches;
    return (ref < obs);
}

// ================================================================
// Function: operator>
// - Overloaded greater-than comparison.
// - Parameters:
// - obj (FeetInches&): Object to compare against.
// ================================================================
bool FeetInches::operator>(FeetInches& obj){
    int ref = (feet * 12) + inches;
    int obs = (obj.feet * 12) + obj.inches;
    return (ref > obs);
}

// ================================================================
// Function: operator==
// - Overloaded equality comparison.
// - Parameters:
// - obj (FeetInches&): Object to compare against.
// ================================================================
bool FeetInches::operator==(FeetInches& obj){
    int ref = (feet * 12) + inches;
    int obs = (obj.feet * 12) + obj.inches;
    return (ref == obs);
}

// ================================================================
// Function: operator++
// - Prefix and postfix increment placeholders.
// ================================================================
void FeetInches::operator++(){}
void FeetInches::operator++(int){}
