// C++Testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Utilities.h"

int main() 
{
    srand(time(0));
    int ComputerGuess = rand() % 10;
    int AnswerAmmount = 6;
    std::string answer;
    Utilities utils;                     // create an instance
    std::cout << "Welcome To This AMAZING Number Guesser\n";
    std::cout << "Simply enter a number and the Computer will tell you if it was too high or low\n";
    std::cout << "You Only Get 5 Tries\n" << "Good Luck :)\n";

    int answer2 = 1;
    while (answer2 != 0 && AnswerAmmount != 1) 
    {
        AnswerAmmount -= 1;
        std::cout << "\n";
        std::cout << "Enter a number: ";
        std::cout << "You Got " << AnswerAmmount << " attempts left :)";

        std::getline(std::cin, answer);

        int value;
        try 
        {
            value = utils.stringToInt(answer); 
        }
        catch (const std::exception& e) 
        {
            std::cerr << "Error: " << e.what() << '\n';
            return 1;
        }

        std::cout << "You entered: " << value << '\n';
        answer2 = utils.CheckComputersGuess(value, ComputerGuess);
    } 

    if (AnswerAmmount == 1) 
    {
        std::cout << "No more attempts, nice try";
    }
}