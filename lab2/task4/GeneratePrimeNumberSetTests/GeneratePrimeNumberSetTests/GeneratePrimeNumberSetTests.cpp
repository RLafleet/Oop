#define CATCH_CONFIG_MAIN
#include "../../../../Catch2/catch.hpp"
#include "GenerateNumbers.h"

TEST_CASE("GeneratePrimeNumbersSet function works correctly") {

    SECTION("Generate prime numbers up to 10") {
        std::set<int> result = GeneratePrimeNumbersSet(10);
        std::set<int> expected = { 2, 3, 5, 7 };
        REQUIRE(result == expected);
    }

    SECTION("Generate prime numbers up to 20") {
        std::set<int> result = GeneratePrimeNumbersSet(20);
        std::set<int> expected = { 2, 3, 5, 7, 11, 13, 17, 19 };
        REQUIRE(result == expected);
    }

    SECTION("Generate prime numbers up to 50") {
        std::set<int> result = GeneratePrimeNumbersSet(50);
        std::set<int> expected = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 };
        REQUIRE(result == expected);
    }

    SECTION("Generate prime numbers.") {
        std::set<int> result = GeneratePrimeNumbersSet(31);
        const int numbersInRange = 11;
        REQUIRE(result.size() == numbersInRange);
    }

    SECTION("Generate prime numbers up to 5") {
        std::set<int> result = GeneratePrimeNumbersSet(5);
        std::set<int> expected = { 2, 3, 5 };
        REQUIRE(result == expected);
    }

    SECTION("Generate prime numbers up to 25") {
        std::set<int> result = GeneratePrimeNumbersSet(25);
        std::set<int> expected = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };
        REQUIRE(result == expected);
    }
}

TEST_CASE("GeneratePrimeNumbersSet non-right response") 
{

    SECTION("Generate prime numbers up to 2.") {
        std::set<int> result = GeneratePrimeNumbersSet(2);
        std::set<int> expected = { 2, 3};
        REQUIRE(result != expected);
    }

    SECTION("Generate prime numbers up to 50. Trash elem 30") {
        std::set<int> result = GeneratePrimeNumbersSet(50);
        std::set<int> expected = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 30, 31, 37, 41, 43, 47 };
        REQUIRE(result != expected);
    }
} 

TEST_CASE("Big numbers works correctly") 
{
    SECTION("Generate prime numbers.") {
        std::set<int> result = GeneratePrimeNumbersSet(99999999);
        const int numbersInRange= 5761455;
        REQUIRE(result.size() == numbersInRange);
    }

    SECTION("Generate prime numbers.") {
        std::set<int> result = GeneratePrimeNumbersSet(100000000);
        const int numbersInMaxPossibbleRange = 5761455;
        REQUIRE(result.size() == numbersInMaxPossibbleRange);
    }
}

