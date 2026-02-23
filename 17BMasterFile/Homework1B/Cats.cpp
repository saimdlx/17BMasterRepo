#include "Cats.h"
#include <iostream>
using namespace std;

/*
Name: Saim Ahmed
File Purpose: Cats Class File
*/

void Cats::setWeight(int weight){
    this->weight = weight;
}

void Cats::setColor(string color){
    this->color = color;
}

void Cats::displayInfo(){
    cout << " weighs " << weight << " pounds and is " << color << "." << endl;
}

void Cats::meow(){
    cout << "says: MEOW!" << endl;
}