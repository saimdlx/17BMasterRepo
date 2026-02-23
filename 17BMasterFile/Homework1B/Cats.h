#ifndef CATS_h
#define CATS_h
#include <string>

/*
Name: Saim Ahmed
File Purpose: Cats Class Header File
*/

class Cats{
    public:
    int weight;
    std::string color;

    void setWeight(int weight);
    void setColor(std::string color);
    void displayInfo();
    void meow();
};

#endif