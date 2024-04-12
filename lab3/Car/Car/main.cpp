#include <iostream>
#include "ControlCar.h"

int main()
{
    Car car;
    ControlCar control(car);
	std::string line;   
	while (getline(std::cin, line))
	{
        if (!control.ControlCommand(line))
        {
            std::cout << "Unknown command" << std::endl;
        }
	}
	return EXIT_SUCCESS;
}

