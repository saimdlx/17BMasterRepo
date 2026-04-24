/* 
 * File:   main.cpp
 * Author: Saim Ahmed
 * Created on: April 09, 2026
 * Purpose:  

 */

//System Libraries Here
#include <iostream>
#include <FeetInches.h>
using namespace std;

//User Libraries Here

//Global Variables

//Function Prototypes Here

//Program Execution Begins Here
int main() {
    
    int F = 5;
    int I = -2;

    int tot = ((F * 12) + I);
    int newF = tot / 12;
    int newI = tot % 12;

    cout << newF << " Feet " <<  newI << " Inches " << endl;

    return 0;
}