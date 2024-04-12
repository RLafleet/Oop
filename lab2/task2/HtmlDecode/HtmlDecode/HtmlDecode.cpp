#include <iostream>
#include "Decode.h"

int main()
{
    try
    {
        std::string inputHtmlStr = ReadInputHtmlStr();
        std::string resultString = DecodeHtmlStr(inputHtmlStr);
        OutputHtmlStr(resultString);
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

