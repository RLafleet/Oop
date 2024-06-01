#include "CMyString.h"
#include <cstring>
#include <stdexcept>

char CMyString::EMPTY_STRING[1] = { '\0' };

CMyString::CMyString(const char* pString, size_t length)
	: m_length(length)
	, m_capacity(length + 1)
{
	m_pData = new char[m_capacity];
	std::copy(pString, pString + length, m_pData);
	m_pData[length] = END_OF_STRING;
}

CMyString::CMyString()
	: CMyString(EMPTY_STRING, 0)
{
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, std::strlen(pString))
{
}

CMyString::CMyString(const CMyString& otherObj)
	: CMyString(otherObj.GetStringData(), otherObj.GetLength())
{
}

CMyString::CMyString(CMyString&& otherObj) noexcept
	: m_pData(otherObj.m_pData)
	, m_length(otherObj.m_length)
	, m_capacity(otherObj.m_capacity)
{
	otherObj.m_pData = EMPTY_STRING;
	otherObj.m_length = 0;
	otherObj.m_capacity = 1;
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

size_t CMyString::GetLength() const
{
	return m_length;
}

size_t CMyString::GetCapacity() const
{
	return m_capacity;
}

const char* CMyString::GetStringData() const
{
	return m_pData;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		throw std::out_of_range("Start index out of string length");
	}

	if ((start + length) > m_length)
	{
		length = m_length - start;
	}

	return { &m_pData[start], length };
}

void CMyString::Clear()
{
	delete[] m_pData;
	m_pData = new char[1];
	m_pData[0] = END_OF_STRING;
	m_length = 0;
	m_capacity = 1;
}

CMyString& CMyString::operator=(const CMyString& otherObj)
{
	if (std::addressof(otherObj) != this)
	{
		CMyString temp(otherObj);
		std::swap(m_pData, temp.m_pData);
		std::swap(m_length, temp.m_length);
		std::swap(m_capacity, temp.m_capacity);
	}

	return *this;
}

CMyString& CMyString::operator=(CMyString&& otherObj) noexcept
{
	if (std::addressof(otherObj) != this)
	{
		delete[] m_pData;
		m_length = 0;
		m_capacity = 1;
		m_pData = EMPTY_STRING;

		std::swap(m_pData, otherObj.m_pData);
		std::swap(m_length, otherObj.m_length);
		std::swap(m_capacity, otherObj.m_capacity);
	}

	return *this;
}

CMyString& CMyString::operator+=(CMyString const& otherObj)
{
	if (std::addressof(otherObj) == this)
	{
		CMyString temp(*this);
		return *this += temp;
	}

	if (m_length + otherObj.m_length + 1 > m_capacity)
	{
		m_capacity = (m_length + otherObj.m_length + 1) * 2;
		char* newData = new char[m_capacity];
		std::memcpy(newData, m_pData, m_length);
		if (m_pData != EMPTY_STRING)
		{
			delete[] m_pData;
		}
		m_pData = newData;
	}
	std::memcpy(m_pData + m_length, otherObj.m_pData, otherObj.m_length + 1);
	m_length += otherObj.m_length;
	return *this;
}

const char& CMyString::operator[](size_t index) const
{
	if (index >= m_length)
	{
		throw std::out_of_range("index is out of range");
	}

	return m_pData[index];
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::out_of_range("index is out of range");
	}

	return m_pData[index];
}

CMyString operator+(CMyString const& myString1, CMyString const& myString2)
{
	CMyString result;
	result.m_length = myString1.m_length + myString2.m_length;
	result.m_capacity = (result.m_length + 1) * 2;
	result.m_pData = new char[result.m_capacity];

	std::memcpy(result.m_pData, myString1.m_pData, myString1.m_length);
	std::memcpy(result.m_pData + myString1.m_length, myString2.m_pData, myString2.m_length);
	result.m_pData[result.m_length] = CMyString::END_OF_STRING;

	return result;
}

CMyString operator+(const std::string& string1, const CMyString& myString2)
{
	return CMyString(string1) + myString2;
}

CMyString operator+(const char* string1, const CMyString& myString2)
{
	return CMyString(string1) + myString2;
}

CMyString operator+(const CMyString& myString1, const std::string& string2)
{
	return myString1 + CMyString(string2);
}

CMyString operator+(const CMyString& myString1, const char* string2)
{
	return myString1 + CMyString(string2);
}

bool operator==(CMyString const& myString1, CMyString const& myString2)
{
	if (myString1.GetLength() != myString2.GetLength())
	{
		return false;
	}

	return memcmp(myString1.GetStringData(),
			   myString2.GetStringData(),
			   myString1.GetLength())
		== 0;
}

bool operator!=(CMyString const& myString1, CMyString const& myString2)
{
	return !(myString1 == myString2);
}

bool operator>(CMyString const& myString1, CMyString const& myString2)
{
	size_t minLength = std::min(myString1.GetLength(), myString2.GetLength());

	return memcmp(myString1.GetStringData(),
			   myString2.GetStringData(),
			   minLength)
		> 0;
}

bool operator>=(CMyString const& myString1, CMyString const& myString2)
{
	size_t minLength = std::min(myString1.GetLength(), myString2.GetLength());

	return memcmp(myString1.GetStringData(),
			   myString2.GetStringData(),
			   minLength)
		>= 0;
}

bool operator<(CMyString const& myString1, CMyString const& myString2)
{
	size_t minLength = std::min(myString1.GetLength(), myString2.GetLength());

	return memcmp(myString1.GetStringData(),
			   myString2.GetStringData(),
			   minLength)
		< 0;
}

bool operator<=(CMyString const& myString1, CMyString const& myString2)
{
	size_t minLength = std::min(myString1.GetLength(), myString2.GetLength());

	return memcmp(myString1.GetStringData(),
			   myString2.GetStringData(),
			   minLength)
		<= 0;
}

std::ostream& operator<<(std::ostream& stream, const CMyString& myString)
{
	stream << myString.GetStringData();

	return stream;
}

std::istream& operator>>(std::istream& stream, CMyString& myString)
{
	size_t resultDataSize = 1;
	size_t resultLength = 0;
	char* resultData = new char[resultDataSize];
	char ch;

	while (
		stream.get(ch)
		&& ch != CMyString::INPUT_STRING_SEPARATOR
		&& ch != CMyString::END_OF_LINE)
	{
		resultData[resultLength] = ch;
		resultLength++;

		if (resultLength == resultDataSize)
		{
			char* newResultData = new char[resultDataSize * 2];
			memcpy(newResultData, resultData, resultDataSize);
			delete[] resultData;
			resultData = newResultData;

			resultDataSize *= 2;
		}
	}

	resultData[resultLength] = CMyString::END_OF_STRING;

	delete[] myString.m_pData;
	myString.m_length = resultLength;
	myString.m_pData = resultData;
	myString.m_capacity = resultDataSize;

	return stream;
}

CMyString::~CMyString()
{
	if (m_pData != EMPTY_STRING)
	{
		delete[] m_pData;
	}
}