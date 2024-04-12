#include "GenerateNumbers.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::set<int> primeSet;
    int n = upperBound;
    std::vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = false;

    for (int p = 3; p * p <= n; p += 2)
    {
        if (prime[p])
        {

            int step = (p == 2) ? p : p * 2;
            for (int i = p * p; i <= n; i += step)
            {
                prime[i] = false;
            }
        }
    }

    primeSet.insert(2);
    for (int i = 3; i <= n; i += 2)
    {
        if (prime[i])
        {
            primeSet.insert(i);
        }
    }

    return primeSet;
}

void WriteNumberPrimeNumbersSet(const std::set<int>& set)
{
    bool someBody = true;
    std::cout << "Prime set number" << std::endl;
    std::cout << set.size() << std::endl;
}