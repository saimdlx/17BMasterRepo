#include "FeetInches.h"
#include <iostream>
using namespace std;

FeetInches::FeetInches() : feet{0}, inches{0} {}

FeetInches::~FeetInches(){}

void FeetInches::simplify(){}

FeetInches& operator+(FeetInches& obj){}
FeetInches& operator-(FeetInches& obj){}

void FeetInches::operator++(){}
void FeetInches::operator++(int){}

ostream &operator<<(ostream &out, FeetInches &obj){}
istream &operator>>(istream &in, FeetInches &obj){}