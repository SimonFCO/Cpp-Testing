#include <iostream>
#include "Utilities.h"

float Calculator()
{
	float result = 0;
	std::string answer;
	int answerInt;
	bool AnswerGotten = false;
	std::cout << "Hello, This is the calculator app\nWhat will your starting number be?\n";

	std::getline(std::cin, answer);
	result = std::stoi(answer);
	while (!AnswerGotten) {
		system("cls");
		std::cout << "Current Number: " << result;
		std::cout << "\nChoose from 4 options,\n[1]:Add\n[2]:Subtract\n[3]:Multiply\n[4]:Divide\n";
		std::getline(std::cin, answer);
		answerInt = std::stoi(answer);

		if (answerInt == 1) 
		{
			std::cout << "+";
			std::getline(std::cin, answer);
			answerInt = std::stoi(answer);
			result = result + answerInt;
			std::cout << "Current Number: "<<result;			
		}
		else if (answerInt == 2) 
		{
			std::cout << "-";
			std::getline(std::cin, answer);
			answerInt = std::stoi(answer);
			result = result - answerInt;
			std::cout << "Current Number: " << result;
		}
		else if (answerInt == 3)
		{
			std::cout << "*";
			std::getline(std::cin, answer);
			answerInt = std::stoi(answer);
			result = result * answerInt;
			std::cout << "Current Number: " << result;
		}
		else if (answerInt == 4) 
		{
			std::cout << "/";
			std::getline(std::cin, answer);
			answerInt = std::stoi(answer);
			result = result / answerInt;
			std::cout << "Current Number: " << result;
		}

		std::cout << "\nChoose from 2 options,\n[1]:Continue\n[2]:Stop\n";
		std::getline(std::cin, answer);
		answerInt = std::stoi(answer);
		if (answerInt == 1) 
		{

		}
		else if (answerInt == 2) 
		{
			AnswerGotten = true;
		}
	}
	return result;
}