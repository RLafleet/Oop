#include "GenerateNumbers.h"

void CheckNumber(int number)
{
    if ((number <= LOWER_BOUND) || (number > UPPER_BOUND))
    {
        throw std::invalid_argument("Enter valid number");
    }
    return;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    // выяснить в каком порядке хранятся элементы set. Выяснил
    // проверка валидности номера. Исправлено
    std::set<int> primeSet;
    CheckNumber(upperBound);
    int n = upperBound;
    std::vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = false;

    //Доработать тесты на <=. Исправлено
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

    auto hint = primeSet.begin();
    hint = primeSet.emplace_hint(hint, 2);
    for (int i = 3; i <= n; i += 2)
    {
        if (prime[i])
        {
            hint = primeSet.emplace_hint(hint, i);
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