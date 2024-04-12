#pragma once
#include <iostream>
#include <string>
#include <regex>
#include <map>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
};

void ParseStr();
bool ParseURL(const std::string& url, Protocol& protocol, std::string& host, int& port, std::string& document);


