#define CATCH_CONFIG_MAIN
#include "../../../../Catch2/catch.hpp"
#include "Translate.h"
#ifdef _WIN32
#include <windows.h>
#endif

#ifdef _WIN32
void setConsoleEncoding(UINT codePage) {
    SetConsoleOutputCP(codePage);
}
#endif

TEST_CASE("Translate function works correctly") {
#ifdef _WIN32
    setConsoleEncoding(1251);
#endif

    SECTION("Translate a word from pairOne to pairTwo") {
        REQUIRE(Translate("кошка, кот", "cat", "кошка") == true);
    }

    SECTION("Translate a word from pairTwo to pairOne") {
        REQUIRE(Translate("кошка, кот", "cat", "cat") == true);
    }

    SECTION("Translate a word that is not in the pair") {
        REQUIRE(Translate("кошка, кот", "cat", "dog") == false);
    }
}

TEST_CASE("TranslateWords function works correctly") {
    std::multimap<std::string, std::string> dictionary;
    dictionary.insert(std::make_pair("кошка, кот", "cat"));

    SECTION("Translate a word from the dictionary") {
        std::string inStr = "кошка";
        REQUIRE(TranslateWords(dictionary, inStr) == true);
    }

    SECTION("Translate a word not in the dictionary") {
        std::string inStr = "собака";
        REQUIRE(TranslateWords(dictionary, inStr) == false);
    }
}

TEST_CASE("SaveNewWord function works correctly") {
    std::multimap<std::string, std::string> dictionary;

    SECTION("Save a new word to the dictionary") {
        SaveNewWord(dictionary, "собака");
        REQUIRE(dictionary.find("собака") != dictionary.end());
    }

    SECTION("Reject saving a new word to the dictionary") {
        SaveNewWord(dictionary, "");
        REQUIRE(dictionary.find("") == dictionary.end());
    }
}

