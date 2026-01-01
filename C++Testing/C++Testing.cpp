#include <iostream>
#include "Utilities.h"
#include "NumberGuesser.h"
#include "Calculator.h"
#include "Galaxy.h"

int main() 
{
	std::cout << "What mode do you want to pick?\n";
	std::cout << "[1]:Number Guesser\n[2]:Calculator\n[3]:Galaxy Simulator\n";
	std::string answer;
	std::getline(std::cin, answer);

	if (answer == "1") 
	{
		system("cls");
		NumberGuesserStart();
	}
	else if (answer == "2") 
	{
		system("cls");
		Calculator();
	}
	else if (answer == "3") 
	{
		system("cls");
		GalaxyStart();
	}		
}