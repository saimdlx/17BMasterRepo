#ifndef PRESIDENTS_H
#define PRESIDENTS_H
#include <string>
using namespace std;

class Presidents {

    public:
        int number;
        string name = "";
        string quote = "";
    
        Presidents();
        ~Presidents();
        void setNumber(int number);
        void setName(string name);
        void setQuote(string quote);
        void displayPresidents();
};
#endif