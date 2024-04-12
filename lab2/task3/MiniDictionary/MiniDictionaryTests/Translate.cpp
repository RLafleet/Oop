#include "Translate.h"
#include "fstream"
#include <sstream>

std::string getWordFromOutputStream()
{
	std::string input;
	if (!(getline(std::cin, input)))
	{
		throw std::runtime_error("Cannot get line from standard output stream");
	}

	return input;
}

std::multimap<std::string, std::string> DictionaryFromFile(const std::string& dictionaryFileName)
{
	std::ifstream dictionaryFile(dictionaryFileName);

	if (!dictionaryFile.is_open())
	{
		throw std::runtime_error("Failed to open for reading");
	}

	std::multimap<std::string, std::string> dictionary;
	std::string line;

	while (std::getline(dictionaryFile, line)) {
		std::istringstream iss(line);
		std::string token;
		std::vector<std::string> pairWords;

		while (std::getline(iss, token, ':')) {
			pairWords.push_back(token);
		}

		dictionary.insert(std::make_pair(pairWords[0], pairWords[1]));
	}

	dictionaryFile.close();

	return dictionary;
}

bool Translate(const std::string& pairOne, const std::string& pairTwo, const std::string& word)
{
	std::istringstream iss(pairOne);
	std::string token;

	while (std::getline(iss, token, ','))
	{
		std::string lowercaseToken = token;
		std::transform(lowercaseToken.begin(), lowercaseToken.end(), lowercaseToken.begin(), ::tolower);

		if (word == lowercaseToken)
		{
			std::cout << word << " translates as " << pairTwo << std::endl;
			return true;
		}
	}
	return false;
}

bool TranslateWords(const std::multimap<std::string, std::string>& dictionary, std::string& word)
{
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);
	for (const auto& pair : dictionary)
	{

		if (Translate(pair.first, pair.second, word))
		{
			return true;
		}
		if (Translate(pair.second, pair.first, word))
		{
			return true;
		}
	}

	return false;;
}

void SaveNewWord(std::multimap<std::string, std::string>& dictionary, const std::string& word)
{
	std::cout << "Unknown word " << word << ". Enter translate of that word or enter empty strong for reject saving." << std::endl;
	std::string input;

	if (!(getline(std::cin, input)))
	{
		throw std::runtime_error("Cannot get line from standard output stream");
	}

	if (input == "")
	{
		std::cout << "Word " << word << " was ignor." << std::endl;
	}
	else
	{
		dictionary.insert(std::pair<std::string, std::string>(word, input));
	}
}

void ProcessDictionary(std::multimap<std::string, std::string>& dictionary)
{
	std::string inputStr;
	std::cout << "For exit enter ..." << std::endl;

	if (!(getline(std::cin, inputStr)))
	{
		throw std::runtime_error("Cannot get line from standard output stream");
	}

	while (inputStr != "...")
	{

		if (inputStr != "" && !TranslateWords(dictionary, inputStr))
		{
			SaveNewWord(dictionary, inputStr);
		}
		std::cout << ">";
		std::getline(std::cin, inputStr);
	}
}

void SaveDictionary(const std::multimap<std::string, std::string>& dictionary, const std::string& dictionaryFileName)
{
	std::ofstream dictionaryFile(dictionaryFileName);

	if (!dictionaryFile.is_open())
	{
		throw std::runtime_error("Failed to open for reading");
	}

	for (auto pair : dictionary)
	{
		dictionaryFile << pair.first << ":" << pair.second << std::endl;
	}
}