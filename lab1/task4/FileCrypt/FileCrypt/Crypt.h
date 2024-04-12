#include <string>

enum class OperatingMode
{
    CRYPT,
    DECRYPT
};

void Transform(const std::string& inputFileName, const std::string& outputFileName, int key, OperatingMode mode);
