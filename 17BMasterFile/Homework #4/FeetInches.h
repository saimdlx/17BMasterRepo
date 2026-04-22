#ifndef FEETINCHES_H
#define FEETINCHES_H

#include <iostream>
using namespace std;

class FeetInches{
    private:
        int feet;
        int inches;
        void simplify();
    public:
        FeetInches();
        ~FeetInches();

        FeetInches operator+(FeetInches&);
        FeetInches operator-(FeetInches&);

        void operator++();
        void operator++(int);

        friend ostream &operator<<(ostream&, FeetInches&);
        friend istream &operator>>(istream&, FeetInches&);

};

#endif