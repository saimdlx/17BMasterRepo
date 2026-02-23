#include "Presidents.h"
#include <iostream>
using namespace std;

Presidents::Presidents() : number(0) , name(""), quote("") {}

Presidents::~Presidents() {}

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
    
    cout << "The Presidents are: " << endl;
    cout << name << ", " << number << "th President" << ", " <<  "said: " << endl;
    cout << "\t" << "\"" << quote << "\"" << endl;

}

