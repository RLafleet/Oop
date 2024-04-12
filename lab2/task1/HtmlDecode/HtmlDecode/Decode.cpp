#include "Decode.h"

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
        if (!specCharFound)
        {
            decodedStr += c;
            partStr = "";
        }

        if (specCharFound) 
        {
            partStr += c;
            specCharFound = true;
            if (partStr == "quot;") 
            {
                specCharFound = false;
            }
            else if (partStr == "apos;") 
            {
                specCharFound = false;
            }
            else if (partStr == "lt;") 
            {
                specCharFound = false;
            }
            else if (partStr == "gt;") 
            {
                specCharFound = false;
            }
            else if (partStr == "amp;") 
            {
                specCharFound = false;
            }
            else 
            {
                if (partStr.size() > 5) 
                {
                    specCharFound = false; 
                    decodedStr += partStr;
                }
            }
        }

        if (c == '&')
        {
            specCharFound = true;
        }
        
    }

    return decodedStr;
}

void OutputHtmlStr(std::string& str)
{
	if (!(std::cout << str << std::endl))
	{
		throw std::runtime_error("Failed to display str to output");
	}
}