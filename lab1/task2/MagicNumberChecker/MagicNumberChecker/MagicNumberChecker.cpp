#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdexcept>

const std::string FIND = "-find";

struct CommandArgs 
{
    std::string attribute;
    std::string number;
};

bool convertToUint64(const std::string& arg, uint64_t& number) {
    try 
    {
        number = std::stoull(arg);
    }
    catch (const std::invalid_argument&) 
    {
        std::cout << "Invalid input number" << std::endl;
        return false;
    }
    catch (const std::out_of_range& ) 
    {
        std::cout << "Number out of range" << std::endl;
        return false;
    }
    return true;
}

bool CheckIfMagicNumber(const std::string& magicNumber)
{
    std::ofstream outputFile("output.txt");
    uint64_t number;

    if (!outputFile.good())
    {
		std::cout << "Error to write in file" << std::endl;
        return false;
    }

    if (!convertToUint64(magicNumber, number))
    {
        return false;
    }

    outputFile << "Non-magic" << std::endl;
    std::cout << "Non-magic" << std::endl;

    if (!outputFile.flush())
    {
		std::cout << "Error to write in file" << std::endl;
		return false;
    }

    return true;
}

bool FindMagicNumbers(const std::string& magicNumber)
{
    std::ofstream output("output.txt");
    uint64_t numberCheckLimit;

    if (!IsOutFileGood(output))
    {
        return false;
    }

    if (!convertToUint64(magicNumber, numberCheckLimit))
    {
        return false;
    }

    std::cout << "Magic numbers do not exist in the range [0, " << numberCheckLimit << "]." << std::endl;
    output << "Magic numbers do not exist in the range [0, " << numberCheckLimit << "]." << std::endl;

    return true; 
}

bool CheckMagicNumber(const std::string& findAttribute, const std::string& magicNumber)
{

    bool success = false;
    
    std::cout << findAttribute;
    if (findAttribute.empty() && !magicNumber.empty())
    {
        success = CheckIfMagicNumber(magicNumber);
    }
    else
    {
        success = FindMagicNumbers(magicNumber);
    }

    if (!success)
    {
        return false;
    }
    return true;
}

bool CheckArguments(int& argc)
{
	if (argc < 2 || argc > 3)
	{
		std::cout << "Usage: <-find> <number>" << std::endl;
		std::cout << "Flag <-find> is optional" << std::endl;
		return false;
	}
	return true;
}

bool ParseArgs(int argc, char* argv[], CommandArgs& args)
{
    if (!CheckArguments(argc))
    {
        return false;
    }

    if (argc == 3 && std::string(argv[1]) == FIND)
    {
        args.attribute = argv[1];
        args.number = argv[2];
    }
    else
    {
        args.number = argv[1];
    }

    return true;

}

int main(int argc, char* argv[])
{
    CommandArgs args;
	if (!ParseArgs(argc, argv, args))
    {
        return 1;
    }

    if (!CheckMagicNumber(args.attribute, args.number))
    {
        return 1;
    }

    std::cout << "Success" << std::endl;
}