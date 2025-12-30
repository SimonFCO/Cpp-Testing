#include <string>
#ifndef UTILITIES_H
#define UTILITIES_H

class Utilities 
{
public:
    // Constructor (optional)
    Utilities() = default;

    // Example member function: converts a string to int safely
    int stringToInt(const std::string& s) const;
    int CheckComputersGuess(const int answer, const int Computer) const;

    // Add any other functions you need here
};

#endif // UTILITIES_H
