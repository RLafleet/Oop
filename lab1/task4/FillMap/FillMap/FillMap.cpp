#include <iostream>
#include "FillMap.h"

struct ConsoleArgs
{
    std::string inputFileName;
    std::string outputFileName;
    int key{};
};

ConsoleArgs PrepareArgs(int argc, const char* argv[])
{
    if (argc != 5)
    {
        throw std::invalid_argument("Invalid number of arguments.\nUsage: <crypt>|<decrypt> <input.txt> <output.txt> <key>");
    }

    ConsoleArgs args;

    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    try
    {
        args.key = std::stoi(argv[3]);
    }
    catch (const std::exception&)
    {
        std::invalid_argument("Key is not valid.\nUsage number from 0 to 255");
    }

    return args;
}

int main(int argc, const char* argv[])
{
    try
    {
        ConsoleArgs args = PrepareArgs(argc, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

