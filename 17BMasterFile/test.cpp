/* 
 * File:   main.cpp
 * Author: Saim Ahmed
 * Created on: April 09, 2026
 * Purpose:  

 */

//System Libraries Here
#include <iostream>
using namespace std;

//User Libraries Here

//Global Variables

//Function Prototypes Here
string setString(int);

//Program Execution Begins Here
int main() {
    int num = 1;
    string foo = setString(num);
    cout << foo << endl;
    return 0;
}

string setString(int newWord){
    string newVal = "";
    if (newWord == 1){
        newVal = "Not a banana";
    }
    return newVal;
}