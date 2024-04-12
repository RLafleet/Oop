#include "ParseStr.h"

int main()
{
	try
	{
		ParseStr();
		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
