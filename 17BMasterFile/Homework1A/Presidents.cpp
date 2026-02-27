/* 
 * File:   Presidents.cpp
 * Author: Saim Ahmed
 * Created on: February 25, 2026
 * Purpose:  Presidents Class Initialization File
 */

//System Libraries Here
#include "Presidents.h"
#include <iostream>
using namespace std;

//Default Constructor & Destructor
Presidents::Presidents() : number(0) , name(""), quote("") {}

Presidents::~Presidents() {}

//Header functions initialized
void Presidents::setNumber(int newNumber){
    number = newNumber;
}

void Presidents::setName(string newName){
    name = newName;
}   

void Presidents::setQuote(string newQuote){
    quote = newQuote;
}

void Presidents::displayPresidents(){
    cout << name << ", " << number << "th President" << ", " <<  "said: " << endl;
    cout << "\t" << "\"" << quote << "\"" << endl;
}