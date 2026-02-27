/* 
 * File:   main.cpp
 * Author: Saim Ahmed
 * Created on: February 25, 2026
 * Purpose:  Cats Class Source File
 */

//System Libraries Here
#include "Cats.h"
#include <iostream>
using namespace std;

//Program Execution Begins Here
int main() {
    
    //Create named cat objects
    Cats Fluffy, Tom, Kitty;
    int weight = 0;
    string color = "";

    //Prompt user for information about weight and color
    cout << "So you have three cats...";
    cout << "\n";

    cout << "Describe Fluffy. What does she weigh? ";
    cin >> weight;
    cin.ignore();

    cout << "What color is she? ";
    cin >> color;
    cin.ignore();

    cout << "\n";

    Fluffy.setWeight(weight);
    Fluffy.setColor(color);

    cout << "Describe Tom. What does he weigh? ";
    cin >> weight;
    cin.ignore();

    cout << "What color is he? ";
    cin >> color;
    cin.ignore();

    cout << "\n";

    Tom.setWeight(weight);
    Tom.setColor(color);

    cout << "Describe Kitty. What does she weigh? ";
    cin >> weight;
    cin.ignore();

    cout << "What color is she? ";
    cin >> color;
    cin.ignore();
    
    Kitty.setWeight(weight);
    Kitty.setColor(color);

    cout << "\n";

    //Display Cat attributes

    cout << "Fluffy ";
    Fluffy.displayInfo();
    cout << "Tom";
    Tom.displayInfo();
    cout << "Kitty";
    Kitty.displayInfo();

    cout << "\n";

    cout << "Fluffy ";
    Fluffy.meow();
    cout << "Tom ";
    Tom.meow();
    cout << "Kitty ";
    Kitty.meow();

    return 0;
}

/*
Output:
So you have three cats...
Describe Fluffy. What does she weigh? 4
What color is she? brown

Describe Tom. What does he weigh? 9
What color is he? orange

Describe Kitty. What does she weigh? 5
What color is she? white

Fluffy  weighs 4 pounds and is brown.
Tom weighs 9 pounds and is orange.
Kitty weighs 5 pounds and is white.

Fluffy says: MEOW!
Tom says: MEOW!
Kitty says: MEOW!
*/