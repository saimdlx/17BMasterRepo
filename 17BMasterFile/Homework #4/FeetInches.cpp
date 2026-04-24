#include "FeetInches.h"
#include <iostream>
using namespace std;

FeetInches::FeetInches(int feet, int inches) {
    this->feet = feet;
    this->inches = inches;
    this->simplify();
}

FeetInches::~FeetInches(){}

void FeetInches::simplify(){

    int totInches = ((feet * 12) + inches);
    feet = totInches / 12;
    inches = totInches % 12;

}

FeetInches FeetInches::operator+(const FeetInches& obj){
    FeetInches sum((feet + obj.feet), (inches + obj.inches));
    sum.simplify();
    return sum;
}

FeetInches FeetInches::operator-(const FeetInches& obj){
    FeetInches diff((feet - obj.feet), (inches - obj.inches));
    diff.simplify();
    return diff;
}

bool FeetInches::operator<(FeetInches& obj){
    int ref = (feet * 12) + inches;
    int obs = (obj.feet * 12) + obj.inches;
    return (ref < obs);
}

bool FeetInches::operator>(FeetInches& obj){
    int ref = (feet * 12) + inches;
    int obs = (obj.feet * 12) + obj.inches;
    return (ref > obs);
}

bool FeetInches::operator==(FeetInches& obj){
    int ref = (feet * 12) + inches;
    int obs = (obj.feet * 12) + obj.inches;
    return (ref == obs);
}

void FeetInches::operator++(){}
void FeetInches::operator++(int){}