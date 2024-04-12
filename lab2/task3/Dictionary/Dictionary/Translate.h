#pragma once
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include "fstream"
#include <sstream>	

bool TranslateWords(const std::multimap<std::string, std::string>& dictionary, const std::string& word);
std::multimap<std::string, std::string> DictionaryFromFile(const std::string& dictionaryFileName);
void ProcessingDictionary(std::multimap<std::string, std::string>& dictionary);
void SaveNewWord(std::multimap<std::string, std::string>& dictionary, const std::string& word);
void SaveDictionary(const std::multimap<std::string, std::string>& dictionary, const std::string& dictionaryFileName);
bool Translate(const std::string& pairOne, const std::string& pairTwo, const std::string& word);
void SaveWord(std::multimap<std::string, std::string>& dictionary, const std::string& word, const std::string& input);