#include "./DivideVector.h"

std::vector<double> ReadInputToVector()
{
    std::cout << "Enter float numbers separated by spaces:\n";
    std::string input;
    std::getline(std::cin, input);

    std::vector<double> vec;
    std::istringstream iss(input);
    double number;

    // цикл поправить, бесконечный
    bool continueLoop = true;
    while (continueLoop) {
        if (!(iss >> number)) {
            if (iss.eof()) {
                continueLoop = false;
            }
            else {
                throw std::runtime_error("Enter correct float numbers");
            }
        }
        else {
            vec.push_back(number);
        }
    }

    return vec;
}

std::vector<double> ResponceVector(std::vector<double>& vec)
{
    if (vec.empty())
    {
       return vec;
    }

    std::vector<double> resultVec = vec;
    double maxElement = *std::max_element(resultVec.begin(), resultVec.end());

    if (maxElement == 0)
    {
        return vec;
    }

    for (auto& element : resultVec)
    {
        element = element / (maxElement / 2);
    }
    return resultVec;
}

void SortVector(std::vector<double>& vec)
{
    std::sort(vec.begin(), vec.end());
}


// дописать тесты
void OutputVector(const std::vector<double>& vec)
{
    std::copy(vec.begin(), vec.end(),
        std::ostream_iterator<double>(std::cout << std::fixed << std::setprecision(3), " "));
    std::cout << std::endl;
}
