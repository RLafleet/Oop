#include "Replace.h"

std::string Replace(const std::string& subject,
    const std::string& searchString, const std::string& replacementString)
{
    if (subject.empty() || searchString.empty())
    {
        return subject;
    }

    size_t pos = 0;

    std::string result;
    while (pos < subject.length())
    {
        size_t foundPos = subject.find(searchString, pos);
        if (foundPos == std::string::npos)
        {
            result.append(subject, pos);
            return result;
        }

        result.append(subject, pos, foundPos - pos);
        result += replacementString;
        pos = foundPos + searchString.length();
    }
    return result;
}

bool ReplaceLines(std::ifstream& inputFile, std::ofstream& outputFile,
    const std::string& searchString, const std::string& replacementString)
{
    if (!inputFile.good() || !outputFile.good())
    {
        return false;
    }

    std::string subject;
    while (std::getline(inputFile, subject))
    {
        
        if (!(outputFile << Replace(subject, searchString, replacementString) << std::endl))
        {
            std::cout << "Failed to write" << std::endl;
            return false;
        }
    }

    if (!outputFile.flush())
    {
        std::cout << "Failed to save on disk";
        return false;
    }

    return true;
}

bool StringReplace(const std::string& inputFileName, const std::string& outputFileName,
    const std::string& searchString, const std::string& replacementString)
{
    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName);

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        std::cout << "Error while opening file" << std::endl;
        return false;
    }

    if (!ReplaceLines(inputFile, outputFile, searchString, replacementString))
    {
        return false;
    }
    return true;
}
