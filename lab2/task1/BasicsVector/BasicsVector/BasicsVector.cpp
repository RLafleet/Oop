#include "./DivideVector.h"

int main()
{
    try
    {
        std::vector<double> vector = ReadInputToVector();
        vector = ResponceVector(vector);
        SortVector(vector);
        OutputVector(vector);
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

