// C++Testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Utilities.h"

int main() {
    srand(time(0));
    int ComputerGuess = rand() % 10;
    std::string answer;
    Utilities utils;                     // create an instance


    int answer2 = 1;
    while (answer2 != 0) {
        std::cout << "Enter a number: ";
        std::getline(std::cin, answer);

        int value;
        try {
            value = utils.stringToInt(answer);   // call the class method
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
            return 1;
        }

        std::cout << "You entered: " << value << '\n';
        answer2 = utils.CheckComputersGuess(value, ComputerGuess);
    } 
}