#include "Replace.h"

struct CommandArgs {
    std::string inputFileName;
    std::string outputFileName;
    std::string searchString;
    std::string replacementString;
};

bool CheckArguments(int& argc)
{
    if (argc != 5)
    {
        std::cout << "Usage: <inputFileName> <outputFileName> <replacement string> <replace string>" << std::endl;
        return false;
    }
    return true;
}

//Parse
bool ParseArgs(int argc, char* argv[], CommandArgs& args)
{
    if (!CheckArguments(argc))
    {
        return false;
    }

    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    args.searchString = argv[3];
    args.replacementString = argv[4];

    return true;

}

int main(int argc, char* argv[]) 
{
    CommandArgs args;
    if (!ParseArgs(argc, argv, args))
    {
        return 1;
    }

    if (!StringReplace(args.inputFileName, args.outputFileName, args.searchString, args.replacementString))
    {
        return 1;
    }
    std::cout << "Success" << std::endl;
}
