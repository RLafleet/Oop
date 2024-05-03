#include <iostream>

const std::string COMMAND_INPUT_ARGS = "cin";

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
        throw std::runtime_error("Failed to open input file");
    }
}

int main(int argc, char* argv[])
{
    try
    {
        Args args = ParseArgs(argc, argv);

        if (args.inputStr != COMMAND_INPUT_ARGS)
        {

        }
        else
        {

        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}