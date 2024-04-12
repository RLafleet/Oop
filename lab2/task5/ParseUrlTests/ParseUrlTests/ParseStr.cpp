#include "ParseStr.h"

const int MAX_POSSIBLE_PORT = 65535;
const int MIN_POSSIBLE_PORT = 0;

void CheckPort(int port)
{
	if (port <= MIN_POSSIBLE_PORT || port >= MAX_POSSIBLE_PORT)
	{
		throw std::invalid_argument("Enter port in range 1 to 65535");
	}
}

bool ParseURL(const std::string& url, Protocol& protocol, std::string& host, int& port, std::string& document)
{
	std::regex url_regex(R"((https?|ftp)://([^:/]+)(?::(\d{1,10}))?(?:/([^:]*))?$)");
	std::smatch url_match;

	if (std::regex_match(url, url_match, url_regex))
	{
		protocol = (url_match[1] == "https") ? Protocol::HTTPS : (url_match[1] == "ftp") ? Protocol::FTP : Protocol::HTTP;
		host = url_match[2];
		port = url_match[3].matched ? std::stoi(url_match[3]) : (protocol == Protocol::HTTPS) ? 443 : (protocol == Protocol::FTP) ? 21 : 80;
		CheckPort(port);
		document = url_match[4];
		return true;
	}
	return false;
}

void ParseStr()
{
	std::string url;

	std::cout << "Enter url to parse. If you want to exit then press enter" << std::endl;

	do
	{
		Protocol protocol = Protocol::NONE;
		std::string host;
		int port;
		std::string document;
		if (!(getline(std::cin, url)) && url != "")
		{
			throw std::runtime_error("Cannot get line from standard output stream");
		}

		if (ParseURL(url, protocol, host, port, document))
		{
			switch (protocol) {
			case Protocol::HTTP:
				std::cout << "Protocol: HTTP" << std::endl;
				break;
			case Protocol::HTTPS:
				std::cout << "Protocol: HTTPS" << std::endl;
				break;
			case Protocol::FTP:
				std::cout << "Protocol: FTP" << std::endl;
				break;
			default:
				std::cout << "Protocol: none" << std::endl;
				break;
			}
			std::cout << "HOST: " << host << std::endl;
			std::cout << "PORT: " << port << std::endl;
			std::cout << "DOC: " << document << std::endl;
		}
		else
		{
			std::cout << "Failed to parses because of invalid URL - " << url << std::endl;
		}
	} while (url != "");
	return;
}

