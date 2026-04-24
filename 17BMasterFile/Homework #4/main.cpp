/* 
 * File:   main.cpp
 * Author: Saim Ahmed
 * Created on: April 21, 2026
 * Purpose:  Purpose
 */

//System Libraries Here
#include <iostream>
#include "FeetInches.h"
using namespace std;

ostream &operator<<(ostream &out, FeetInches& obj){
    out << obj.feet << " feet, " << obj.inches << " inches." << endl;
    return out;
}

istream &operator>>(istream &in, FeetInches& obj){
    cout << "Feet: ";
    in >> obj.feet;
    cout << "Inches: ";
    in >> obj.inches;
    obj.simplify();
    return in;
}

//Program Execution Begins Here
int main() {
    FeetInches obj1;
    FeetInches obj2;
    cout << "Enter a distance in feet and inches. " << endl;
    cin >> obj1;
    cout << "Enter another distance in feet and inches. " << endl;
    cin >> obj2;
    cout << "The values you entered are: " << '\n';
    cout << obj1 << " and " << obj2 << endl;
    FeetInches sum = obj1 + obj2;
    FeetInches diff = obj1 - obj2;
    cout << "Sum: " << endl;
    cout << sum << endl;
    cout << "Diff: " << endl;
    cout << diff << endl;
    cout << "First < Second : " << ((obj1 < obj2) ? "true" : "false") << '\n';
    return 0;
}