#pragma once
#include <iostream>
#include <string>
#include <regex>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
	NONE
};

void ParseStr();
bool ParseURL(const std::string& url, Protocol& protocol, std::string& host, int& port, std::string& document);


