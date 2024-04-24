// geometricFigures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct Args 
{
    std::string inputStr;
};

Args ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        throw std::invalid_argument("Invalid count of arguments\nUsage: <input_str>");
    }
    
    Args args;
    args.inputStr = argv[1]; 
    return args;
}

std::ifstream GetFileName(const std::string& inputStr)
{
    std::ifstream inputFile(inputStr);
    return inputFile;
}

void CheckForOpenFile(std::ifstream& inputFile)
{
    if (!inputFile.is_open())
    {
        throw std::runtime_error("Failed to open input stream file");
    }
}

int main(int argc, char* argv[])
{
    try
    {
        Args args = ParseArgs(argc, argv);
        std::cout << args.inputStr << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}