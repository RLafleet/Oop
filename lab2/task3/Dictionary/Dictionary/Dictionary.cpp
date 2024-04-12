#include "Translate.h"
#include <Windows.h>

std::string ParseInputFileName(int argc, char* argv[])
{
    if (argc != 2)
    {
        throw std::invalid_argument("Invalid number of arguments.\nUsage: <dictionary.txt> ");
    }


    std::string dictionaryFileName = argv[1];

    return dictionaryFileName;
}

int main(int argc, char* argv[])
{
    system("chcp 1251");

    try 
    {
        std::string dictionaryFileName = ParseInputFileName(argc, argv);
        std::multimap<std::string, std::string> dictionary = DictionaryFromFile(dictionaryFileName);
        size_t sizePrimaryDictionary = dictionary.size();
        ProcessingDictionary(dictionary);
        if (sizePrimaryDictionary != dictionary.size())
        {
            SaveDictionary(dictionary, dictionaryFileName);
        }
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

