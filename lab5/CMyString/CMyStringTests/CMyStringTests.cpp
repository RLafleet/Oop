#define CATCH_CONFIG_MAIN 
#include <stdexcept>

#include "../../../Catch2/catch.hpp"
#include "../CMyString/CMyString.h"

using std::string;

TEST_CASE("test string")
{
	const string expectedString = "test str";
	const string giveString = "test str";

	CMyString myString(giveString);

	REQUIRE(myString.GetStringData() == expectedString);
}

TEST_CASE("Default str")
{
	CMyString str;
	const string expectedString = "";
	
	REQUIRE(str.GetLength() == 0);
	REQUIRE(str.GetStringData() == expectedString);
	REQUIRE(str.GetCapacity() == 1);
}

TEST_CASE("Check length")
{
	const char* testData = "Some string";
	const string expectedString = "Some string";

	CMyString str(testData);
	REQUIRE(str.GetLength() == 11);
	REQUIRE_THAT(str.GetStringData(), Catch::Matchers::Equals(expectedString));
	REQUIRE(str.GetCapacity() == 12);
}

TEST_CASE("String with length")
{
	const char* testData = "Test String";
	const string expectedString = "Test";

	size_t length = 4;
	CMyString str(testData, length);
	REQUIRE(str.GetLength() == length);
	REQUIRE_THAT(str.GetStringData(), Catch::Matchers::Equals(expectedString));
	REQUIRE(str.GetCapacity() == length + 1);
}

TEST_CASE("Compare copy str constructor")
{
	const char* testData = "Test String";
	const string expectedString = "Test String";

	CMyString original(testData);
	CMyString copy(original);
	REQUIRE(copy.GetLength() == original.GetLength());
	REQUIRE(copy.GetLength() == 11);
	REQUIRE_THAT(copy.GetStringData(), Catch::Matchers::Equals(original.GetStringData()));
	REQUIRE(copy.GetStringData() == expectedString);
	REQUIRE(copy.GetCapacity() == 12);
}

TEST_CASE("Move constructor")
{
	const char* testData = "Test String";
	const string expectedString = "Test String";

	CMyString original(testData);
	CMyString moved(std::move(original));
	REQUIRE(moved.GetLength() == 11);
	REQUIRE(moved.GetStringData() == expectedString);
	REQUIRE(moved.GetCapacity() == 12);
	REQUIRE(original.GetLength() == 0);
	REQUIRE_THAT(original.GetStringData(), Catch::Matchers::Equals(""));
	REQUIRE(original.GetCapacity() == 1);
}

TEST_CASE("Param str")
{
	std::string testData = "Test String";
	const string expectedString = "Test String";

	CMyString str(testData);
	REQUIRE(str.GetLength() == 11);
	REQUIRE_THAT(str.GetStringData(), Catch::Matchers::Equals(expectedString));
	REQUIRE(str.GetCapacity() == 12);
}

TEST_CASE("Length check")
{
	const char* testData = "Test String";

	CMyString str(testData);
	REQUIRE(str.GetLength() == 11);
}

TEST_CASE("Capacity check")
{
	const char* testData = "Test String";

	CMyString str(testData);
	REQUIRE(str.GetCapacity() == 12);
}

TEST_CASE("Sub str")
{
	const char* testData = "Test String";
	const string expectedString = "String";

	CMyString str(testData);
	CMyString subStr = str.SubString(5, 6);
	REQUIRE(subStr.GetLength() == 6);
	REQUIRE_THAT(subStr.GetStringData(), Catch::Matchers::Equals(expectedString));
	REQUIRE(subStr.GetCapacity() == 7);
}

TEST_CASE("Sub str out of range")
{
	const char* testData = "Test String";
	CMyString str(testData);

	REQUIRE_THROWS_AS(str.SubString(20, 5), std::out_of_range);
}

TEST_CASE("Check clear on empty str")
{
	CMyString str;
	str.Clear();

	REQUIRE(str.GetLength() == 0);
	REQUIRE_THAT(str.GetStringData(), Catch::Matchers::Equals(""));
	REQUIRE(str.GetCapacity() == 1);
}

TEST_CASE("Check clear on not empty str")
{
	const char* testData = "Test String";
	CMyString str(testData);
	str.Clear();

	REQUIRE(str.GetLength() == 0);
	REQUIRE_THAT(str.GetStringData(), Catch::Matchers::Equals(""));
	REQUIRE(str.GetCapacity() == 1);
}

TEST_CASE("Check assigment")
{
	const string expectedString = "Test String";
	CMyString str("Test String");
	{
		auto newStr = str;

		REQUIRE(newStr.GetLength() == 11);
		REQUIRE_THAT(newStr.GetStringData(), Catch::Matchers::Equals(expectedString));
		REQUIRE(newStr.GetCapacity() == 12);
		
		newStr.Clear();

		REQUIRE(newStr.GetLength() == 0);
		REQUIRE_THAT(newStr.GetStringData(), Catch::Matchers::Equals(""));
		REQUIRE(newStr.GetCapacity() == 1);
	}

	REQUIRE(str.GetLength() == 11);
	REQUIRE_THAT(str.GetStringData(), Catch::Matchers::Equals(expectedString));
	REQUIRE(str.GetCapacity() == 12);
}

TEST_CASE("Check self assignment")
{
	CMyString str("Test String");
	const string expectedString = "Test String";

	str = str;

	REQUIRE(str.GetLength() == 11);
	REQUIRE_THAT(str.GetStringData(), Catch::Matchers::Equals(expectedString));
	REQUIRE(str.GetCapacity() == 12);
	str.Clear();
	REQUIRE(str.GetLength() == 0);
	REQUIRE_THAT(str.GetStringData(), Catch::Matchers::Equals(""));
	REQUIRE(str.GetCapacity() == 1);
}

TEST_CASE("Operation move")
{
	const char* testData = "Test String";
	const string expectedString = "Test String";

	CMyString original(testData);
	CMyString moved = std::move(original);
	REQUIRE(moved.GetLength() == 11);
	REQUIRE_THAT(moved.GetStringData(), Catch::Matchers::Equals(expectedString));
	REQUIRE(moved.GetCapacity() == 12);
	REQUIRE(original.GetLength() == 0);
	REQUIRE_THAT(original.GetStringData(), Catch::Matchers::Equals(""));
	REQUIRE(original.GetCapacity() == 1);
}

TEST_CASE("Operator addition with one empty string")
{
	CMyString str1;
	CMyString str2("Test");
	str1 += str2;
	const string expectedString = "Test";

	REQUIRE(str1.GetLength() == 4);
	REQUIRE_THAT(str1.GetStringData(), Catch::Matchers::Equals(expectedString));
	REQUIRE(str1.GetCapacity() == 10);
}

TEST_CASE("Operator addition with two empty string")
{
	CMyString str1;
	CMyString str2;
	str1 += str2;

	REQUIRE(str1.GetLength() == 0);
	REQUIRE_THAT(str1.GetStringData(), Catch::Matchers::Equals(""));
	REQUIRE(str1.GetCapacity() == 1);
}

TEST_CASE("Operator addition with no empty str")
{
	CMyString str1("Pen");
	CMyString str2(" ApplePen");
	str1 += str2;
	const string expectedString = "Pen ApplePen";

	REQUIRE(str1.GetLength() == 12);
	REQUIRE_THAT(str1.GetStringData(), Catch::Matchers::Equals(expectedString));
	REQUIRE(str1.GetCapacity() == 26);
}

TEST_CASE("Operatorm addition with self str")
{
	CMyString str("JUJu");
	const string expectedString = "JUJuJUJu";
	str += str;

	REQUIRE(str.GetLength() == 8);
	REQUIRE_THAT(str.GetStringData(), Catch::Matchers::Equals(expectedString));
	REQUIRE(str.GetCapacity() == 18);
}

TEST_CASE("Operatorm addition with self empty str")
{
	CMyString str;
	str += str;
	const string expectedString = "";

	REQUIRE(str.GetLength() == 0);
	REQUIRE_THAT(str.GetStringData(), Catch::Matchers::Equals(expectedString));
	REQUIRE(str.GetCapacity() == 1);
}

TEST_CASE("Different additional check")
{
	CMyString str("I");
	str += CMyString(" need") += CMyString(" you");
	const string expectedString = "I need you";

	REQUIRE(str.GetLength() == 10);
	REQUIRE_THAT(str.GetStringData(), Catch::Matchers::Equals(expectedString));
	REQUIRE(str.GetCapacity() == 22);
}

TEST_CASE("Check index")
{
	const char* testData = "I need you";
	CMyString str(testData);

	for (size_t i = 0; i < str.GetLength(); ++i)
	{
		REQUIRE(str[i] == testData[i]);
	}
}

TEST_CASE("Index out of range")
{
	CMyString str("I need you");
	REQUIRE_THROWS_AS(str[str.GetLength()], std::out_of_range);
}

TEST_CASE("Index out of range with empty str")
{
	CMyString str;
	REQUIRE_THROWS_AS(str[0], std::out_of_range);
}

TEST_CASE("Check several indexes")
{
	const char* testData = "gojo satore";
	CMyString str(testData);

	REQUIRE(str[0] == 'g');
	REQUIRE(str[5] == 's');
	REQUIRE(str[10] == 'e');
}

TEST_CASE("Check several indexes after assignment at index")
{
	char testData[] = "I need you";
	CMyString str(testData);
	str[0] = 'i';
	str[2] = 'n';

	REQUIRE(str[0] == 'i');
	REQUIRE(str[2] == 'n');
}

TEST_CASE("Index assignment out of range")
{
	char testData[] = "Test String";
	CMyString str(testData);
	REQUIRE_THROWS_AS(str[str.GetLength()] = 'X', std::out_of_range);
}

TEST_CASE("Index assignment out of range with empty str")
{
	CMyString str;
	REQUIRE_THROWS_AS(str[0] = 'X', std::out_of_range);
}

TEST_CASE("Check special symbols at assignment")
{
	char testData[] = "Test String";
	CMyString str(testData);
	str[0] = 't';
	str[5] = 's';
	str[10] = '\0';
	REQUIRE(str[0] == 't');
	REQUIRE(str[5] == 's');
	REQUIRE(str[10] == '\0');
}

TEST_CASE("Check the new str by getting two additional constructors str")
{
	CMyString str1("Hello");
	CMyString str2(" World");
	CMyString result = str1 + str2;
	REQUIRE(result.GetLength() == 11);
	REQUIRE_THAT(result.GetStringData(), Catch::Matchers::Equals("Hello World"));
	REQUIRE(result.GetCapacity() == 24);
}

TEST_CASE("Check the new str by getting two additional constructor str and std str")
{
	std::string stdStr("Hello");
	CMyString str(" World");
	CMyString result = stdStr + str;
	REQUIRE(result.GetLength() == 11);
	REQUIRE_THAT(result.GetStringData(), Catch::Matchers::Equals("Hello World"));
	REQUIRE(result.GetCapacity() == 24);
}

TEST_CASE("Checking addition with char ptr")
{
	const char* charPtr = "Hello";
	CMyString str(" World");
	CMyString result = charPtr + str;
	REQUIRE(result.GetLength() == 11);
	REQUIRE_THAT(result.GetStringData(), Catch::Matchers::Equals("Hello World"));
	REQUIRE(result.GetCapacity() == 24);
}

TEST_CASE("Check the new str by getting two additional constructor str and std str with other additional position")
{
	CMyString str("Hello");
	std::string stdStr(" World");
	CMyString result = str + stdStr;
	REQUIRE(result.GetLength() == 11);
	REQUIRE_THAT(result.GetStringData(), Catch::Matchers::Equals("Hello World"));
	REQUIRE(result.GetCapacity() == 24);
}

TEST_CASE("Check equals operations with different length")
{
	CMyString str1("Test");
	CMyString str2("Testing");
	REQUIRE((str1 == str2) == false);
	REQUIRE(str1 != str2);
}

TEST_CASE("Check equals operations with self text")
{
	CMyString str("Test");
	REQUIRE(str == str);
	REQUIRE((str != str) == false);
}

TEST_CASE("Check operations compare with different text")
{
	CMyString str1("apple");
	CMyString str2("banana");
	REQUIRE(str1 < str2);
	REQUIRE((str1 >= str2) == false);
	REQUIRE((str1 > str2) == false);
	REQUIRE(str1 <= str2);

	CMyString str3("hello");
	CMyString str4("world");
	REQUIRE(str4 > str3);
	REQUIRE(str4 >= str3);
	REQUIRE((str4 < str3) == false);
	REQUIRE((str4 <= str3) == false);

	CMyString str5("test");
	CMyString str6("test");
	REQUIRE((str5 > str6) == false);
	REQUIRE(str5 >= str6);
	REQUIRE((str5 < str6) == false);
	REQUIRE(str5 <= str6);
}

TEST_CASE("Check operations compare with empty text")
{
	CMyString str1;
	CMyString str2;
	REQUIRE((str1 > str2) == false);
	REQUIRE(str1 >= str2);
	REQUIRE((str1 < str2) == false);
	REQUIRE(str1 <= str2);
}

TEST_CASE("Check operations compare with self text")
{
	CMyString str("apple");
	REQUIRE((str > str) == false);
	REQUIRE(str >= str);
	REQUIRE((str < str) == false);
	REQUIRE(str <= str);
}

TEST_CASE("Check stringstream result")
{
	CMyString str("Test String");
	std::stringstream ss;
	ss << str;

	REQUIRE_THAT(ss.str(), Catch::Matchers::Equals("Test String"));
}

TEST_CASE("Check input result")
{
	CMyString str;
	std::stringstream ss("Hello World!");
	ss >> str;

	REQUIRE(str.GetLength() == 5);
	REQUIRE_THAT(str.GetStringData(), Catch::Matchers::Equals("Hello"));
}

TEST_CASE("Check input and stringstream result")
{
	CMyString str("Hello World!");
	std::stringstream ss;
	ss << str;
	ss >> str;

	REQUIRE(str.GetLength() == 5);
	REQUIRE_THAT(str.GetStringData(), Catch::Matchers::Equals("Hello"));
}

TEST_CASE("Checking addition with char ptr with other additional position")
{
	CMyString str("Hello");
	const char* charPtr = " World";
	CMyString result = str + charPtr;
	REQUIRE(result.GetLength() == 11);
	REQUIRE_THAT(result.GetStringData(), Catch::Matchers::Equals("Hello World"));
	REQUIRE(result.GetCapacity() == 24);
}

TEST_CASE("Check double capacity")
{
	CMyString str1("Hello");
	size_t initialCapacity = str1.GetCapacity() * 2;
	CMyString str2(" World!");

	str1 += str2;

	REQUIRE(str1.GetLength() == 12);
	REQUIRE_THAT(str1.GetStringData(), Catch::Matchers::Equals("Hello World!"));
	REQUIRE(str1.GetCapacity() >= initialCapacity * 2);
}

TEST_CASE("Double capacity with add")
{
	CMyString str1("Hello");
	size_t initialCapacity = str1.GetCapacity();
	CMyString str2(" World!");

	CMyString result = str1 + str2;

	REQUIRE(result.GetLength() == 12);
	REQUIRE_THAT(result.GetStringData(), Catch::Matchers::Equals("Hello World!"));
	REQUIRE(result.GetCapacity() >= initialCapacity * 2);
}

TEST_CASE("Capacity and data for cycle of same chars")
{
	CMyString str1("A");
	size_t initialCapacity = str1.GetCapacity();
	CMyString str2("Z");

	for (int i = 0; i < 20; ++i)
	{
		str1 += str2;
	}

	REQUIRE(str1.GetLength() == 21);
	REQUIRE_THAT(str1.GetStringData(), Catch::Matchers::Equals("AZZZZZZZZZZZZZZZZZZZZ"));
	REQUIRE(str1.GetCapacity() >= initialCapacity);
	REQUIRE(str1.GetCapacity() == 30);
}

TEST_CASE("Capacity and data for cycle of same chars, result to stt")
{
	CMyString str1("A");
	size_t initialCapacity = str1.GetCapacity();
	CMyString str2("Z");
	CMyString result = str1;

	for (int i = 0; i < 20; ++i)
	{
		result = result + str2;
	}

	REQUIRE(result.GetLength() == 21);
	REQUIRE_THAT(result.GetStringData(), Catch::Matchers::Equals("AZZZZZZZZZZZZZZZZZZZZ"));
	REQUIRE(result.GetCapacity() >= initialCapacity * 2);
}

TEST_CASE("Check equals operations with same text")
{
	CMyString str1("Test");
	CMyString str2("Test");
	REQUIRE(str1 == str2);
	REQUIRE((str1 != str2) == false);
}

TEST_CASE("Check equals operations with different text")
{
	CMyString str1("Hello");
	CMyString str2("World");
	REQUIRE((str1 == str2) == false);
	REQUIRE(str1 != str2);
}

TEST_CASE("Check equals operations with empty text")
{
	CMyString str1;
	CMyString str2;
	REQUIRE(str1 == str2);
	REQUIRE((str1 != str2) == false);
}

