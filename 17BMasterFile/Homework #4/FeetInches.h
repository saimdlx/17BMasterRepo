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
        FeetInches(int feet = 0, int inches = 0);
        ~FeetInches();

        FeetInches operator+(const FeetInches&);
        FeetInches operator-(const FeetInches&);

        void operator++();
        void operator++(int);

        bool operator<(FeetInches&);
        bool operator>(FeetInches&);
        bool operator==(FeetInches&);
        
        friend ostream &operator<<(ostream&, FeetInches&);
        friend istream &operator>>(istream&, FeetInches&);

};

#endif