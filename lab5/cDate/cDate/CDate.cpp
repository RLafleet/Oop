#include "CDate.h"

const std::vector<unsigned> CDate::DAYS_IN_MONTH = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

//std::vector на std::array
const std::vector<unsigned> CDate::DAYS_TO_MONTH = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

//заменить на std::array
const std::map<unsigned, WeekDay> CDate::NUMBER_OF_WEEKDAY = {
	{ 1, WeekDay::THURSDAY },
	{ 2, WeekDay::FRIDAY },
	{ 3, WeekDay::SATURDAY },
	{ 4, WeekDay::SUNDAY },
	{ 5, WeekDay::MONDAY },
	{ 6, WeekDay::TUESDAY },
	{ 0, WeekDay::WEDNESDAY }
};

char CDate::DELIMITER = ':';

CDate::CDate(unsigned int day, Month month, unsigned year)
{
	if (!IsValid(day, month, year))
	{
		throw std::invalid_argument("Invalid CDate");
	}

	m_days += day - MIN_AVAILIABLE_DAY;
	m_days += DAYS_TO_MONTH.at(static_cast<int>(month) - 1);

	int yearCircle = static_cast<int>(year);
	// цикл убрать.
	m_days += CalculateDays(year);
	if (month > Month::FEBRUARY && IsLeapYear(yearCircle))
	{
		m_days += 1;
	}
}

CDate::CDate(unsigned int timestamp)
{
	m_days += timestamp;

	if (GetYear() < MIN_AVAILIBALE_YEAR || GetYear() > MAX_AVAILIBALE_YEAR)
	{
		throw std::invalid_argument("Invalid CDate");
	}
}

bool CDate::IsFebraury(unsigned int monthIndex)
{
	if (monthIndex == static_cast<int>(Month::FEBRUARY))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CDate::ExceedsDays(int indexByMonth, unsigned days, unsigned daysInMonth, unsigned year)
{
	if (indexByMonth == static_cast<int>(Month::FEBRUARY))
	{
		return days > daysInMonth + IsLeapYear(year);
	}
	else
	{
		return days > daysInMonth;
	}
}

unsigned CDate::CalculateDays(int year)
{
	return static_cast<int>((year - MIN_AVAILIBALE_YEAR) * DAYS_IN_YEAR
		+ (year - MIN_AVAILIBALE_YEAR) / 4
		- (year - MIN_AVAILIBALE_YEAR) / 100
		+ (year - MIN_AVAILIBALE_YEAR) / 400);
}

unsigned CDate::GetDay() const
{
	// выглядит сложно, упростить
	unsigned year = MIN_AVAILIBALE_YEAR;
	unsigned days = m_days;

	year = static_cast<unsigned>(year + days / DAYS_IN_YEAR_ACCURATE);
	days -= CalculateDays(year);

	for (unsigned index = 0; index < DAYS_IN_MONTH.size(); index++)
	{
		unsigned indexByMonth = index + 1;
		unsigned daysInMonth = DAYS_IN_MONTH.at(index);

		if (ExceedsDays(indexByMonth, days, daysInMonth, year))
		{
			days -= daysInMonth;
			if (IsFebraury(indexByMonth))
			{
				days -= IsLeapYear(year);
			}
		}
		else
		{
			break;
		}
	}
	return days;
}

Month CDate::GetMonth() const
{
	unsigned year = MIN_AVAILIBALE_YEAR;
	unsigned days = m_days;

	year = static_cast<unsigned>(year + days / DAYS_IN_YEAR_ACCURATE);
	days -= CalculateDays(year);

	Month month = static_cast<Month>(MIN_AVAILIBALE_MONTH);
	unsigned daysOfMonth = 0;
	for (unsigned index = 0; index < DAYS_IN_MONTH.size(); index++)
	{
		unsigned indexByMonth = index + 1;
		unsigned daysInMonth = DAYS_IN_MONTH.at(index);

		if (ExceedsDays(indexByMonth, days, daysOfMonth, year))
		{
			daysOfMonth += daysInMonth;
			if (IsFebraury(indexByMonth))
			{
				daysOfMonth += IsLeapYear(year);
			}
			month = static_cast<Month>(indexByMonth);
		}
		else
		{
			break;
		}
	}
	return month;
}

unsigned CDate::GetYear() const
{
	unsigned year = MIN_AVAILIBALE_YEAR;
	unsigned days = m_days;

	year = static_cast<unsigned>(year + days / DAYS_IN_YEAR_ACCURATE);
	return year;
}

WeekDay CDate::GetWeekDay() const
{
	return NUMBER_OF_WEEKDAY.at(m_days % DAYS_OF_WEEK);
}

bool CDate::IsLeapYear(unsigned year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool CDate::IsValid(unsigned int day, Month month, unsigned int year)
{
	bool isValidMonth = (static_cast<int>(month) >= MIN_AVAILIBALE_MONTH)
		&& (static_cast<int>(month) <= MAX_AVAILIBALE_MONTH);

	bool isValidDay = false;
	if (isValidMonth)
	{
		isValidDay = (day >= MIN_AVAILIABLE_DAY)
			&& (day <= DAYS_IN_MONTH.at(static_cast<int>(month) - 1) + IsLeapYear(year));
	}

	bool isValidYear = (year >= MIN_AVAILIBALE_YEAR)
		&& (year <= MAX_AVAILIBALE_YEAR);

	return isValidYear && isValidMonth && isValidDay;
}

CDate& CDate::operator++()
{
	++m_days;
	return *this;
}

CDate CDate::operator++(int)
{
	CDate temp(*this);
	++(*this);
	return temp;
}

CDate& CDate::operator--()
{
	--m_days;
	return *this;
}

CDate CDate::operator--(int)
{
	CDate temp(*this);
	--(*this);
	return temp;
}

CDate CDate::operator+(int days) const
{
	return CDate(m_days + days - MIN_AVAILIABLE_DAY);
}

CDate CDate::operator-(int days) const
{
	return CDate(m_days - days - MIN_AVAILIABLE_DAY);
}

int CDate::operator-(const CDate& date2) const
{
	auto deltaDays = static_cast<int>(m_days) - static_cast<int>(date2.m_days);

	return deltaDays;
}

CDate& CDate::operator+=(int days)
{
	m_days += static_cast<unsigned>(days);
	return *this;
}

CDate& CDate::operator-=(int days)
{
	m_days -= static_cast<unsigned>(days);
	return *this;
}

bool CDate::operator==(const CDate& date) const
{
	return m_days == date.m_days;
}

bool CDate::operator!=(const CDate& date) const
{
	return m_days != date.m_days;
}

bool CDate::operator<(const CDate& date) const
{
	return m_days < date.m_days;
}

bool CDate::operator>(const CDate& date) const
{
	return m_days > date.m_days;
}

bool CDate::operator<=(const CDate& date) const
{
	// добавть тесты на операции сравнения с отрицательным результатом
	return m_days <= date.m_days;
}

bool CDate::operator>=(const CDate& date) const
{
	return m_days >= date.m_days;
}

CDate operator+(int days, const CDate& cDate)
{
	return CDate(cDate.m_days + days - CDate::MIN_AVAILIABLE_DAY);
}

// форматирование
std::ostream& operator<<(std::ostream& os, const CDate& date)
{
	os << date.GetDay() << CDate::DELIMITER << static_cast<int>(date.GetMonth()) << CDate::DELIMITER << date.GetYear();
	return os;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
	unsigned int day;
	unsigned year;
	int month;
	char dot;
	is >> day >> dot >> month >> dot >> year;
	if (dot != CDate::DELIMITER)
	{
		is.setstate(std::ios::badbit);
	}

	date = CDate(day, static_cast<Month>(month), year);
	return is;
}