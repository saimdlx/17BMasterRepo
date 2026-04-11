/* 
 * File:   main.cpp
 * Author: Saim Ahmed
 * Created on: February 25, 2026
 * Purpose:  Presidents Class Source File
 */

//System Libraries Here
#include "Presidents.h"
#include <iostream>
#include <istream>
#include <vector>
using namespace std;


//Program Execution Begins Here
int main() {

    //Create President objects and push them into vector for display.
    Presidents pres1;
    Presidents pres2;
    Presidents pres3;

    vector<Presidents> presidentsList;
    presidentsList.push_back(pres1);
    presidentsList.push_back(pres2);
    presidentsList.push_back(pres3);

    //User defined variables
    string name = "";
    string quote = "";
    int number = 0;

    //User input and display logic
    for (int i = 0 ; i < presidentsList.size() ; i++){

        cout << "Enter the first president's number: ";
        cin >> number;
        

        cin.ignore();

        cout << "Enter his name: ";
        getline(cin, name);
        

        cout << "Enter his quote: ";
        getline(cin, quote);
        
        cout << "\n";

        presidentsList[i].setNumber(number);
        presidentsList[i].setName(name);
        presidentsList[i].setQuote(quote);

    }
    
    cout << "The Presidents are: " << endl;
    for (int i = 0 ; i < presidentsList.size() ; i++){
        presidentsList[i].displayPresidents();
    }

    return 0;
}

/*
Output:
Enter the first president's number: 37
Enter his name: Richard Nixon
Enter his quote: I am not a crook.

Enter the first president's number: 45
Enter his name: Donald Trump
Enter his quote: Is our country stil spending money on the GLOBAL WARMING HOAX?

Enter the first president's number: 42
Enter his name: Bill Clinton
Enter his quote: I did not have sexual relations with that woman.

The Presidents are: 
Richard Nixon, 37th President, said: 
        "I am not a crook."
Donald Trump, 45th President, said: 
        "Is our country stil spending money on the GLOBAL WARMING HOAX?"
Bill Clinton, 42th President, said: 
        "I did not have sexual relations with that woman."
*/