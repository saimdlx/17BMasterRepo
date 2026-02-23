#include "Cats.h"
#include <iostream>
using namespace std;

/*
Name: Saim Ahmed
File Purpose: Cats Class Source File
*/

int main(){

    Cats Fluffy, Tom, Kitty;
    int weight;
    string color;
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