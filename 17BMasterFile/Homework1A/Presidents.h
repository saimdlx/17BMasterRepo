#ifndef PRESIDENTS_H
#define PRESIDENTS_H
#include <string>

/*
Name: Saim Ahmed
File Purpose: Presidents Class Header File
*/

class Presidents {

    public:
        int number;
        std::string name;
        std::string quote;
    
        Presidents();
        ~Presidents();
        void setNumber(int newNumber);
        void setName(std::string newName);
        void setQuote(std::string newQuote);
        void displayPresidents();
};
#endif