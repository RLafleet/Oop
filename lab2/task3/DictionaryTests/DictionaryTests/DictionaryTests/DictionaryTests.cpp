#define CATCH_CONFIG_MAIN
#include "../../../../../Catch2/catch.hpp"
#include "Translate.h"

TEST_CASE("Translate function works correctly") 
{
    std::string pairOne = "кошка, кот";
    std::string pairTwo = "cat";
    std::string word1 = "кошка";
    std::string word2 = "cat";
    std::string word3 = "собака";
    std::string word4 = "CaT";

    SECTION("Translate a word from pairOne to pairTwo") 
    {
        REQUIRE(Translate(pairOne, pairTwo, word1) == true);
    }

    SECTION("Translate a word from pairTwo to pairOne") 
    {
        REQUIRE(Translate(pairTwo, pairOne, word2) == true);
    }

    SECTION("Translate a word that is not in the pair") 
    {
        REQUIRE(Translate(pairOne, pairTwo, word3) == false);
    }

    SECTION("Translate a word from pairTwo to pairOne") 
    {
        REQUIRE(Translate(pairTwo, pairOne, word4) == true);
    }
}

TEST_CASE("TranslateWords function works correctly") 
{
    std::multimap<std::string, std::string> dictionary;
    dictionary.insert(std::make_pair("кошка, кот", "cat"));

    std::string inStr1 = "кошка";
    std::string inStr2 = "собака";

    SECTION("Translate a word from the dictionary") 
    {
        REQUIRE(TranslateWords(dictionary, inStr1) == true);
    }

    SECTION("Translate a word not in the dictionary") 
    {
        REQUIRE(TranslateWords(dictionary, inStr2) == false);
    }
}

TEST_CASE("SaveNewWord function works correctly") 
{
    std::multimap<std::string, std::string> dictionary;
    dictionary.insert(std::make_pair("кошка, кот", "cat"));

    std::string newWord1 = "собака";
    std::string newWord2 = "dog";

    SECTION("Save a new word to the dictionary") 
    {
        SaveWord(dictionary, newWord1, newWord2);
        REQUIRE(dictionary.find(newWord1) != dictionary.end());
    }
    // разобраться с регистром
    // Выбор сохранения или нет. И тесты на сохранения и чтение
    std::string newWord3 = "";

    SECTION("Reject saving a new word to the dictionary") 
    {
        SaveWord(dictionary, newWord1, newWord3);
        REQUIRE(dictionary.find(newWord1) == dictionary.end());
    }
}