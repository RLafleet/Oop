#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

bool IsInFileGood(const std::ifstream& file)
{
    if (!file.good())
    {
        std::cout << "Error reading" << std::endl;
        return false;
    }
    return true;
}

bool IsOutFileGood(const std::ofstream& file)
{
    if (!file.good())
    {
        std::cout << "Error writing" << std::endl;
        return false;
    }
    return true;
}

bool CheckArguments(int argc)
{
    if (argc != 2)
    {
        std::cout << "Usage: <input.txt>" << std::endl;
        return false;
    }
    return true;
}

bool CanOpenInFile(const char* argIn, std::ifstream& inputFile)
{
    std::string inputFileName = argIn;

    inputFile.open(inputFileName);

    if (!inputFile.is_open())
    {
        std::cout << "Error while opening file" << std::endl;
        return false;
    }
    return true;
}


double determinant2x2(double a, double b, double c, double d)
{
    return a * d - b * c;
}

double determinant3x3(const double mat[3][3])
{
    return mat[0][0] * determinant2x2(mat[1][1], mat[1][2], mat[2][1], mat[2][2]) -
        mat[0][1] * determinant2x2(mat[1][0], mat[1][2], mat[2][0], mat[2][2]) +
        mat[0][2] * determinant2x2(mat[1][0], mat[1][1], mat[2][0], mat[2][1]);
}

void Transpose(const double A[3][3], double adj[3][3])
{
    adj[0][0] = determinant2x2(A[1][1], A[1][2], A[2][1], A[2][2]);
    adj[0][1] = -determinant2x2(A[0][1], A[0][2], A[2][1], A[2][2]);
    adj[0][2] = determinant2x2(A[0][1], A[0][2], A[1][1], A[1][2]);
    adj[1][0] = -determinant2x2(A[1][0], A[1][2], A[2][0], A[2][2]);
    adj[1][1] = determinant2x2(A[0][0], A[0][2], A[2][0], A[2][2]);
    adj[1][2] = -determinant2x2(A[0][0], A[0][2], A[1][0], A[1][2]);
    adj[2][0] = determinant2x2(A[1][0], A[1][1], A[2][0], A[2][1]);
    adj[2][1] = -determinant2x2(A[0][0], A[0][1], A[2][0], A[2][1]);
    adj[2][2] = determinant2x2(A[0][0], A[0][1], A[1][0], A[1][1]);
}

bool inverse3x3(const double A[3][3], double inverse[3][3])
{
    double det = determinant3x3(A);
    if (det == 0)
    {
        std::cout << "Determinant is 0. Matrix is same, because of inverting is not allowed." << std::endl;
        return false;
    }

    double adj[3][3];
    Transpose(A, adj);

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            inverse[i][j] = adj[i][j] / det;
        }
    }

    return true;
}

bool RecordMatrix(std::ifstream& inputFile, double matrix[3][3])
{
    if (!IsInFileGood(inputFile))
    {
        return false;
    }

    for (int i = 0; i < 3; ++i)
    {
        std::string line;
        if (!getline(inputFile, line))
        {
            std::cout << "Error matrix data." << std::endl;
            return false;
        }

        std::stringstream ss(line);
        for (int j = 0; j < 3; ++j)
        {
            if (!(ss >> matrix[i][j]))
            {
                std::cout << "Error matrix data." << std::endl;
                return false;
            }
        }
    }
    return true;
}

bool ResponseMatrix(double inverse[3][3])
{
    std::ofstream outputFile("output.txt");
    if (!IsOutFileGood(outputFile))
    {
        return false;
    }
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            outputFile << std::setprecision(3) << std::fixed << inverse[i][j] << " ";
        }
        outputFile << std::endl;
    }

    outputFile.flush();
    if (!IsOutFileGood(outputFile))
    {
        std::cout << "Error writing" << std::endl;
        return false;
    }

    return true;
}

void CopyMatrix(const double source[3][3], double destination[3][3])
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            destination[i][j] = source[i][j];
        }
    }
}

bool InverseMatrix(int argc, char* argv[])
{
    if (!CheckArguments(argc))
    {
        return false;
    }

    std::ifstream inputFile;
    if (!CanOpenInFile(argv[1], inputFile))
    {
        return false;
    }

    double matrix[3][3];

    if (!RecordMatrix(inputFile, matrix))
    {
        return false;
    }

    double inverse[3][3];

    bool isInverseMatrix = inverse3x3(matrix, inverse);

    double rightMatrix[3][3];

    if (isInverseMatrix)
    {
        CopyMatrix(inverse, rightMatrix);
    }
    else
    {
        CopyMatrix(matrix, rightMatrix);
    }

    if (!ResponseMatrix(rightMatrix))
    {
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    if (!InverseMatrix(argc, argv))
    {
        return 1;
    }
    std::cout << "Success" << std::endl;
}
