#include "Presidents.h"
#include <iostream>
#include <istream>
#include <vector>
using namespace std;

/*
Name: Saim Ahmed
File Purpose: Presidents Class Source File
*/

int main(){
    Presidents pres1;
    Presidents pres2;
    Presidents pres3;

    vector<Presidents> presidentsList;
    presidentsList.push_back(pres1);
    presidentsList.push_back(pres2);
    presidentsList.push_back(pres3);

    string name, quote;
    int number;

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