#include "CalculatorHandler.h"

int main()
{
	Calculator calculator;
	CalculatorHandler calculatorHandler = CalculatorHandler(calculator);
	std::string comand;
	calculatorHandler.Handle(std::cin, std::cout);
	return EXIT_SUCCESS;
}
