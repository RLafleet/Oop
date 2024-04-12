#include <iostream>
#include "Crypt.h"

struct ConsoleArgs
{
    OperatingMode mode{};
    std::string inputFileName;
    std::string outputFileName;
    int key{};
};

OperatingMode ValidateMode(std::string modeEncrypt)
{
    if (modeEncrypt == "crypt")
    {
        return OperatingMode::CRYPT;
    }
    else if (modeEncrypt == "decrypt")
    {
        return OperatingMode::DECRYPT;
    }
    else
    {
        throw std::invalid_argument("Invalid chosen mode.\nUsage: <crypt> or <decrypt>");
    }
};

// Parse. Исправлено
// Name. Исправлено
ConsoleArgs ParseArgs(int argc, const char* argv[])
{
    if (argc != 5)
    {
        throw std::invalid_argument("Invalid number of arguments.\nUsage: <crypt>|<decrypt> <input.txt> <output.txt> <key>");
    }

    ConsoleArgs args;

    args.mode = ValidateMode(argv[1]);
    args.inputFileName = argv[2];
    args.outputFileName = argv[3];
    try
    {
        args.key = std::stoi(argv[4]);
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
        ConsoleArgs args = ParseArgs(argc, argv);
        Transform(args.inputFileName, args.outputFileName, args.key, args.mode);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}

