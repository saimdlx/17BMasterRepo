// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: FeetInches Main Program
// ================================================================
// Program Description:
// - Demonstrates usage of the FeetInches class.
// - Takes user input for two distances.
// - Displays sum, difference, and comparison results.
// ================================================================
#include <iostream>
#include "FeetInches.h"
using namespace std;

// ================================================================
// Function: operator<<
// - Overloaded output stream operator for FeetInches.
// - Displays measurement in "X feet, Y inches" format.
// - Parameters:
// - out (ostream&): Output stream.
// - obj (FeetInches&): Object to display.
// ================================================================
ostream &operator<<(ostream &out, FeetInches& obj){
    out << obj.feet << " feet, " << obj.inches << " inches";
    return out;
}

// ================================================================
// Function: operator>>
// - Overloaded input stream operator for FeetInches.
// - Prompts user for feet and inches and simplifies the result.
// - Parameters:
// - in (istream&): Input stream.
// - obj (FeetInches&): Object to populate.
// ================================================================
istream &operator>>(istream &in, FeetInches& obj){
    cout << "Feet: ";
    in >> obj.feet;
    cout << "Inches: ";
    in >> obj.inches;
    obj.simplify();
    return in;
}

// ================================================================
// Main Function:
// - Initializes two FeetInches objects.
// - Performs arithmetic and logical operations on measurements.
// - Displays results to the console.
// ================================================================
int main() {
    // ================================================================
    // Distance Objects:
    // - obj1, obj2: Store user-entered measurements.
    // ================================================================
    FeetInches obj1;
    FeetInches obj2;
    
    cout << "Enter a distance in feet and inches. " << endl;
    cin >> obj1;
    cout << "Enter another distance in feet and inches. " << endl;
    cin >> obj2;
    
    cout << "The values you entered are: " << endl;
    cout << obj1 << " and " << obj2 << endl;
    
    // ================================================================
    // Calculations:
    // - sum: Total of both distances.
    // - diff: Difference between both distances.
    // ================================================================
    FeetInches sum = obj1 + obj2;
    FeetInches diff = obj1 - obj2;
    
    cout << "Sum: " << endl;
    cout << sum << endl;
    cout << "Difference: " << endl;
    cout << diff << endl;
    
    // ================================================================
    // Comparisons:
    // - Uses overloaded relational operators to compare distances.
    // ================================================================
    cout << "Comparison Results: " << endl;
    cout << "First > Second : " << ((obj1 > obj2) ? "true" : "false") << '\n';
    cout << "First < Second : " << ((obj1 < obj2) ? "true" : "false") << '\n';
    cout << "FIrst == Second : " << ((obj1 == obj2) ? "true" : "false") << '\n';
    
    return 0; // End of Program
}


/*
(base) sameelocal@saimbook Homework #4 % clang++ *.cpp
(base) sameelocal@saimbook Homework #4 % ./a.out
Enter a distance in feet and inches. 
Feet: 5
Inches: 8
Enter another distance in feet and inches. 
Feet: 3
Inches: 11
The values you entered are: 
5 feet, 8 inches and 3 feet, 11 inches
Sum: 
9 feet, 7 inches
Difference: 
1 feet, 9 inches
Comparison Results: 
First > Second : true
First < Second : false
FIrst == Second : false
(base) sameelocal@saimbook Homework #4 % ./a.out
Enter a distance in feet and inches. 
Feet: 2
Inches: 15
Enter another distance in feet and inches. 
Feet: 1
Inches: -5
The values you entered are: 
3 feet, 3 inches and 0 feet, 7 inches
Sum: 
3 feet, 10 inches
Difference: 
2 feet, 8 inches
Comparison Results: 
First > Second : true
First < Second : false
FIrst == Second : false
(base) sameelocal@saimbook Homework #4 % ./a.out
Enter a distance in feet and inches. 
Feet: 4
Inches: 6
Enter another distance in feet and inches. 
Feet: 4
Inches: 6
The values you entered are: 
4 feet, 6 inches and 4 feet, 6 inches
Sum: 
9 feet, 0 inches
Difference: 
0 feet, 0 inches
Comparison Results: 
First > Second : false
First < Second : false
FIrst == Second : true
*/