#include <fstream>
#include "Crypt.h"
#include <functional>
#include <iostream>

const int MIN_ENCRYPTION_KEY = 0;
const int MAX_ENCRYPTION_KEY = 255;

unsigned char Crypt(unsigned char byte, int key)
{
	byte = (byte ^ key);

	unsigned char result = 0;
	
	result |= (byte & 0b00000111) << 2;
	result |= (byte & 0b00011000) << 3;
	result |= (byte & 0b01100000) >> 5;
	result |= (byte & 0b10000000) >> 2;

	return result;
}

unsigned char Decrypt(unsigned char byte, int key)
{
	unsigned char result = 0;
	
	result |= (byte & 0b00000011) << 5;
	result |= (byte & 0b00011100) >> 2;
	result |= (byte & 0b00100000) << 2;
	result |= (byte & 0b11000000) >> 3;
	result ^= key;

	return result;
}

//Дублирование кода. Исправлено
//Выяснить почему 42. Выяснил
//Выяснить когда передача по ссылке. Выяснил
void TransformFile(std::istream& inputFile, std::ostream& outputFile, int key, std::function<uint8_t(uint8_t, int)> process)
{
	char byte;

	if (!inputFile.good())
	{
		throw std::runtime_error("Error reading input file");
	}

	// Один цикл. Исправлено
	while (inputFile.read(&byte, sizeof(byte)))
	{
		byte = process(byte, key);
		outputFile.put(byte);
	}
	
	if (!inputFile.eof())
	{
		throw std::runtime_error("Error reading input file");
	}
}

void ValidateCryptKey(int key)
{
	if (key < MIN_ENCRYPTION_KEY || key > MAX_ENCRYPTION_KEY)
	{
		throw std::invalid_argument("Key not allowed. Key must be from 0 to 255");
	}
}

// Transform. Исправлено
void Transform(const std::string& inputFileName, const std::string& outputFileName, int key, OperatingMode mode)
{
	ValidateCryptKey(key);
	std::ifstream inputFile(inputFileName, std::ios::binary);
	std::ofstream outputFile(outputFileName, std::ios::binary);

	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open for reading");
	}

	if (!outputFile.is_open())
	{
		throw std::runtime_error("Failed to open for writing");
	}

	std::function<unsigned char(unsigned char, int)> f_display_c = Crypt;
	std::function<unsigned char(unsigned char, int)> f_display_d = Decrypt;

	if (mode == OperatingMode::CRYPT)
	{
		TransformFile(inputFile, outputFile, key, Crypt);
	}
	else
	{
		TransformFile(inputFile, outputFile, key, Decrypt);
	}

	if (!outputFile.flush())
	{
		throw std::runtime_error("Failed to saved on disk");
	}
}