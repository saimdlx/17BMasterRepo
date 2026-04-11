/* 
 * File:   Cats.cpp
 * Author: Saim Ahmed
 * Created on: February 25, 2026
 * Purpose:  Cats Class Header File
 */

#ifndef CATS_h
#define CATS_h
#include <string>

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