/* 
 * File:   Cats.cpp
 * Author: Saim Ahmed
 * Created on: February 25, 2026
 * Purpose:  Cats Class Initialization File
 */

//System Libraries Here
#include "Cats.h"
#include <iostream>
using namespace std;

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