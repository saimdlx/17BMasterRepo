/* 
 * File:   main.cpp
 * Author: Saim Ahmed
 * Created on: February 25, 2026
 * Purpose:  Purpose
 */
//System Libraries Here
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//User Libraries Here

//Global Variables

//Function Prototypes Here

//Program Execution Begins Here
int main() {
    
    float angle = 0;
    float angcos = 0;
    float angsin = 0;
    float angtan = 0;

    cout << "Input angle in degrees" << endl;
    cin >> angle;
    float rad;

    rad = angle * (M_PI/180);
    cout << fixed;
    cout << "Cos: " << showpoint << setprecision(4) << cos(rad) << noshowpoint << endl;
    cout << "Sin: " << showpoint << setprecision(4) << sin(rad) << noshowpoint << endl;
    cout << "Tan: " << showpoint << setprecision(4) << tan(rad) << noshowpoint << endl;
    return 0;
}