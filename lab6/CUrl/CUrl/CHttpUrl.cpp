#include "CHttpUrl.h"

const int MAX_POSSIBLE_PORT = 65536;
const int MIN_POSSIBLE_PORT = 0;

bool CheckPort(int port)
{
	if (port <= MIN_POSSIBLE_PORT || port >= MAX_POSSIBLE_PORT)
	{
		return false;
	}
	return true;
}

Protocol getProtocol(const std::string& protocolString)
{
	if (protocolString == "https")
	{
		return Protocol::HTTPS;
	}
	else if (protocolString == "ftp")
	{
		return Protocol::FTP;
	}
	else
	{
		return Protocol::HTTP;
	}
}

int getPort(const std::string& portString, Protocol protocol)
{
	if (!portString.empty())
	{
		return std::stoi(portString);
	}
	else
	{
		switch (protocol)
		{
		case Protocol::HTTPS:
			return 443;
		case Protocol::FTP:
			return 21;
		default:
			return 80;
		}
	}
}

bool ParseURL(const std::string& url, Protocol& protocol, std::string& host, int& port, std::string& document)
{
	std::regex url_regex(R"((https?|ftp)://([^:/]+)(?::(\d{1,6}))?(?:/([^:]*))?$)");
	std::smatch url_match;

	if (std::regex_match(url, url_match, url_regex))
	{
		// вынести в отдельную функцию. Исправлено
		protocol = getProtocol(url_match[1]);
		host = url_match[2];
		// вынести в отдельную функцию. Исправил
		port = getPort(url_match[3], protocol);
		if (!CheckPort(port))
		{
			return false;
		}
		document = url_match[4];
		return true;
	}
	return false;
}

void ParseStr()
{
	std::map<Protocol, std::string> protocolStrings = {
		{ Protocol::HTTP, "HTTP" },
		{ Protocol::HTTPS, "HTTPS" },
		{ Protocol::FTP, "FTP" }
	};

	std::string url;

	std::cout << "Enter url to parse. If you want to exit then write ..." << std::endl;

	do
	{
		// убрать из структуры протокола none. Исправил
		Protocol protocol = Protocol::HTTP;
		std::string host;
		int port;
		std::string document;
		// empty. Исправил
		if (!(getline(std::cin, url)) && !url.empty())
		{
			throw std::runtime_error("Cannot get line from standard output stream");
		}

		if (ParseURL(url, protocol, host, port, document))
		{
			// заменить на MAP. Исправил
			std::cout << "Input URL:\n"
					  << url << std::endl;
			auto it = protocolStrings.find(protocol);
			std::cout << "Protocol: " << it->second << std::endl;
			std::cout << "HOST: " << host << std::endl;
			std::cout << "PORT: " << port << std::endl;
			// Если пустой документ то. Исправил
			std::cout << "DOC: " << (document.empty() ? "/" : document) << std::endl;
		}
		else
		{
			std::cout << "\nFailed to parses because of invalid URL.\n\nInput URL:\n"
					  << url << std::endl;
		}
	} while (url != "...");
	return;
}
// invalid url пустая строка. Исправил
// регистр