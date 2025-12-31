#include <string>
#ifndef UTILITIES_H
#define UTILITIES_H

class Utilities 
{
    public:
        // Constructor
        Utilities() = default;

        int stringToInt(const std::string& s) const;
        int CheckComputersGuess(const int answer, const int Computer) const;
};

#endif // UTILITIES_H
