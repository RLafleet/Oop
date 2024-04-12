#include "GenerateNumbers.h"

unsigned int GetUpperBound()
{
    int number;
    if (!(std::cin >> number) || (number <= LOWER_BOUND) || (number > UPPER_BOUND))
    { 
        throw std::invalid_argument("Enter valid number");
    }
    return number;
}

int main()
{
    try
    {
        std::cout << "Enter number in range from 1 to 100000000" << std::endl;
        int upperBound = GetUpperBound();

        std::set<int> primeNumbersSet = GeneratePrimeNumbersSet(upperBound);
        WriteNumberPrimeNumbersSet(primeNumbersSet);

        return EXIT_SUCCESS;
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

