#include "Utilities.h"
#include <string>
#include <stdexcept>   // for std::invalid_argument, std::out_of_range
#include <iostream>

int Utilities::stringToInt(const std::string& s) const 
{
    try 
    {
        return std::stoi(s);
    }
    catch (const std::invalid_argument&) 
    {
        throw std::invalid_argument("Utilities::stringToInt – not a number\n");
    }
    catch (const std::out_of_range&) {
        throw std::out_of_range("Utilities::stringToInt – number out of range\n");
    }
}

int Utilities::CheckComputersGuess(const int answer, const int Computer) const 
{
    if (answer < Computer) 
    {
        std::cout << "Too small\n";
        return 2;
    }
    else if (answer > Computer) 
    {
        std::cout << "Too Large\n";
        return 1;
    }
    else 
    {
        std::cout << "Correct!!!\n";
        return 0;
    }
    std::cout << "Something has gone terribly wrong\n";
    return 3;
}

static void NumberGuesser(){

}
