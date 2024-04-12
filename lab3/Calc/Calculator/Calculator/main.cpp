#include "CalculatorHandler.h"

int main()
{
	Calculator calculator;
	CalculatorHandler calculatorHandler = CalculatorHandler(calculator);
	std::string comand;
	while (getline(std::cin, comand))
	{
		if (!calculatorHandler.CommandHandler(comand))
		{
			std::cout << "Unknown command" << std::endl;
		}
	}
	return EXIT_SUCCESS;
}
