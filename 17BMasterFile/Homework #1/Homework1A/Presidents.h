/* 
 * File:   Presidents.h
 * Author: Saim Ahmed
 * Created on: February 25, 2026
 * Purpose:  Presidents Class Header File
 */

#ifndef PRESIDENTS_H
#define PRESIDENTS_H
#include <string>

class Presidents {

    public:
        int number = 0;
        std::string name = "";
        std::string quote = "";
    
        Presidents();
        ~Presidents();
        void setNumber(int newNumber);
        void setName(std::string newName);
        void setQuote(std::string newQuote);
        void displayPresidents();
};
#endif