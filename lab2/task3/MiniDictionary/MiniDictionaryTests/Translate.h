#pragma once
#include <iostream>
#include <string>
#include <map>
#include <boost/algorithm/string.hpp>
#include <vector>

bool TranslateWords(const std::multimap<std::string, std::string>& dictionary, std::string& word);
std::multimap<std::string, std::string> DictionaryFromFile(const std::string& dictionaryFileName);
void ProcessDictionary(std::multimap<std::string, std::string>& dictionary);
void SaveNewWord(std::multimap<std::string, std::string>& dictionary, const std::string& word);
void SaveDictionary(const std::multimap<std::string, std::string>& dictionary, const std::string& dictionaryFileName);
bool Translate(const std::string& pairOne, const std::string& pairTwo, const std::string& word);