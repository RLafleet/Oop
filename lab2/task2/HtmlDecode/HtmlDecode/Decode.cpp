#include "Decode.h"

const int MAX_SPECIAL_CHAR_SYMBOLS = 6;

std::string ReadInputHtmlStr()
{
    std::cout << "Enter str:\n";
    std::string input;
    if (!(std::getline(std::cin, input)))
    {
        throw std::runtime_error("Failed to get enter string");
    }

    return input;
}

std::string DecodeHtmlStr(const std::string& strToDecode) {
    std::string decodedStr;
    std::string partStr;
    bool specCharFound = false;

    for (char c : strToDecode) {
        if (c == '&')
        {
            specCharFound = true;
        }

        if (!specCharFound)
        {
            decodedStr += c;
            partStr = "";
        }

        if (specCharFound)
        {
            partStr += c;
            specCharFound = true;
            if (partStr == "&quot;")
            {
                specCharFound = false;
                decodedStr += "\"";
            }
            else if (partStr == "&apos;")
            {
                specCharFound = false;
                decodedStr += "`";
            }
            else if (partStr == "&lt;")
            {
                specCharFound = false;
                decodedStr += "<";
            }
            else if (partStr == "&gt;")
            {
                specCharFound = false;
                decodedStr += ">";
            }
            else if (partStr == "&amp;")
            {
                specCharFound = false;
                decodedStr += "&";
            }
            else
            {
                if (partStr.size() > MAX_SPECIAL_CHAR_SYMBOLS)
                {
                    specCharFound = false;
                    decodedStr += partStr;
                }
            }
        }
    }

    return decodedStr;
}

void OutputHtmlStr(const std::string& str)
{
    if (!(std::cout << str << std::endl))
    {
        throw std::runtime_error("Failed to display str to output");
    }
}