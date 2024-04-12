#define CATCH_CONFIG_MAIN
#include "../../../../Catch2/catch.hpp"
#include "ParseStr.h"

TEST_CASE("ParseURL function works correctly")
{

    SECTION("Valid HTTP URL") {
        std::string url = "http://www.example.com:8080/index.html";
        Protocol protocol = Protocol::FTP; 
        std::string host;
        int port;
        std::string document;
        REQUIRE(ParseURL(url, protocol, host, port, document) == true);
        REQUIRE(protocol == Protocol::HTTP);
        REQUIRE(host == "www.example.com");
        REQUIRE(port == 8080);
        REQUIRE(document == "index.html");
    }

    SECTION("Valid HTTPS URL") {
        std::string url = "https://example.com";
        Protocol protocol = Protocol::HTTP;
        std::string host;
        int port;
        std::string document;
        REQUIRE(ParseURL(url, protocol, host, port, document) == true);
        REQUIRE(protocol == Protocol::HTTPS);
        REQUIRE(host == "example.com");
        REQUIRE(port == 443);
        REQUIRE(document.empty());
    }

    SECTION("Valid FTP URL with default port") {
        std::string url = "ftp://ftp.example.com";
        Protocol protocol = Protocol::HTTP; 
        std::string host;
        int port;
        std::string document;
        REQUIRE(ParseURL(url, protocol, host, port, document) == true);
        REQUIRE(protocol == Protocol::FTP);
        REQUIRE(host == "ftp.example.com");
        REQUIRE(port == 21);
        REQUIRE(document.empty());
    }

}

TEST_CASE("ParseURL invalid tests")
{
    SECTION("Invalid protocol") {
        std::string url = "invalid://example.com:8080/index.html";
        Protocol protocol = Protocol::HTTP; 
        std::string host;
        int port;
        std::string document;
        REQUIRE(ParseURL(url, protocol, host, port, document) == false);
    }

    SECTION("Invalid format") {
        std::string url = "http:/example.com";
        Protocol protocol = Protocol::HTTP;
        std::string host;
        int port;
        std::string document;
        REQUIRE(ParseURL(url, protocol, host, port, document) == false);
    }

    SECTION("Invalid port format") {
        std::string url = "https://example.com:port/index.html";
        Protocol protocol = Protocol::HTTPS; 
        std::string host;
        int port;
        std::string document;
        REQUIRE(ParseURL(url, protocol, host, port, document) == false);
    }

    SECTION("Invalid port format") {
        std::string url = "https://example.com:65536/index.html";
        Protocol protocol = Protocol::HTTPS;
        std::string host;
        int port;
        std::string document;
        REQUIRE_THROWS_AS(ParseURL(url, protocol, host, port, document), std::invalid_argument);
    }
}
