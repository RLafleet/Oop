#ifndef CMYSTRING_H
#define CMYSTRING_H

#include <iostream>

class CMyString
{
public:
	friend CMyString operator+(CMyString const& myString1, CMyString const& myString2);

	friend CMyString operator+(std::string const& string1, CMyString const& myString2);

	friend CMyString operator+(char const* string1, CMyString const& myString2);

	friend CMyString operator+(CMyString const& myString1, std::string const& string2);

	friend CMyString operator+(CMyString const& myString1, char const* string2);

	friend bool operator==(CMyString const& myString1, CMyString const& myString2);

	friend bool operator!=(CMyString const& myString1, CMyString const& myString2);

	friend bool operator>(CMyString const& myString1, CMyString const& myString2);

	friend bool operator>=(CMyString const& myString1, CMyString const& myString2);

	friend bool operator<(CMyString const& myString1, CMyString const& myString2);

	friend bool operator<=(CMyString const& myString1, CMyString const& myString2);

	friend std::ostream& operator<<(std::ostream& stream, CMyString const& myString);

	friend std::istream& operator>>(std::istream& stream, CMyString& myString);

	CMyString();

	explicit CMyString(const char* pString);

	CMyString(const char* pString, size_t length);

	CMyString(CMyString const& other);

	CMyString(CMyString&& other) noexcept;

	explicit CMyString(std::string const& stlString);

	~CMyString();

	[[nodiscard]] size_t GetLength() const;

	[[nodiscard]] size_t GetCapacity() const;

	[[nodiscard]] const char* GetStringData() const;

	[[nodiscard]] CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	void Clear();

	CMyString& operator=(CMyString const& other);

	CMyString& operator=(CMyString&& other) noexcept;

	CMyString& operator+=(CMyString const& other);

	const char& operator[](size_t index) const;

	char& operator[](size_t index);

private:
	constexpr static const char END_OF_STRING = '\0';

	constexpr static const char END_OF_LINE = '\n';

	constexpr static const char INPUT_STRING_SEPARATOR = ' ';

	static char EMPTY_STRING[1];

	size_t m_length;

	size_t m_capacity;

	char* m_pData;
};

#endif // CMYSTRING_H