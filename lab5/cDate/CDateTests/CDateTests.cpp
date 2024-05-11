#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../cDate/CDate.h"
#include <sstream>

const unsigned DAYS_IN_YEAR = 365;

const unsigned MIN_YEAR = 1970;

const unsigned MIN_DAY = 1;

const unsigned DAYS_FIRST_LEAP_YEAR = DAYS_IN_YEAR + DAYS_IN_YEAR + 31 + 28;

TEST_CASE("test default scenario")
{
    CDate cDate;
    unsigned expectedDay = MIN_DAY;
    Month expectedMonth = Month::JANUARY;
    unsigned expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::THURSDAY;

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("test default scenario and operator +")
{
    unsigned timestamp = 0;

    CDate cDate = CDate(timestamp);
    unsigned expectedDay = MIN_DAY + timestamp;
    Month expectedMonth = Month::JANUARY;
    unsigned expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::THURSDAY;

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("test default scenario and plus one day")
{
    unsigned timestamp = 1;

    CDate cDate = CDate(timestamp);
    unsigned expectedDay = MIN_DAY + timestamp;
    Month expectedMonth = Month::JANUARY;
    unsigned expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::FRIDAY;

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("dates minus")
{
    CDate cDate = CDate(25, Month::APRIL, 2024);
    CDate cDate1 = CDate(25, Month::APRIL, 2023);

    REQUIRE(-366 == cDate1 - cDate);
    REQUIRE(WeekDay::THURSDAY == cDate.GetWeekDay());
}

TEST_CASE("test weekday on new month")
{
    unsigned timestamp = 31;

    CDate cDate = CDate(timestamp);
    unsigned expectedDay = 1;
    Month expectedMonth = Month::FEBRUARY;
    unsigned expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::SUNDAY;

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("first leap year 1972 days")
{
    unsigned timestamp = DAYS_FIRST_LEAP_YEAR;

    CDate cDate = CDate(timestamp);
    unsigned expectedDay = 29;
    Month expectedMonth = Month::FEBRUARY;
    unsigned expectedYear = 1972;
    WeekDay expectedWeekDay = WeekDay::TUESDAY;

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("test febraury days")
{
    unsigned timestamp = 58;

    CDate cDate = CDate(timestamp);
    unsigned expectedDay = 28;
    Month expectedMonth = Month::FEBRUARY;
    unsigned expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::SATURDAY;

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("test febraury day")
{
    unsigned expectedDay = 28;
    Month expectedMonth = Month::FEBRUARY;
    unsigned expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::SATURDAY;

    CDate cDate = CDate(expectedDay, expectedMonth, expectedYear);

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("test leap year febraury")
{
    unsigned expectedDay = 29;
    Month expectedMonth = Month::FEBRUARY;
    int expectedYear = 1972;
    WeekDay expectedWeekDay = WeekDay::TUESDAY;

    CDate cDate = CDate(expectedDay, expectedMonth, expectedYear);

    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("throw exception")
{
    REQUIRE_THROWS_AS(CDate(3999999999), std::invalid_argument);
}

TEST_CASE("throw exception2")
{
    REQUIRE_THROWS_AS(CDate(10, Month::FEBRUARY, 10000), std::invalid_argument);

    REQUIRE_THROWS_AS(CDate(10, Month::FEBRUARY, 1969), std::invalid_argument);
}

TEST_CASE("throw exception3")
{
    REQUIRE_THROWS_AS(CDate(-1, Month::FEBRUARY, MIN_YEAR), std::invalid_argument);

    REQUIRE_THROWS_AS(CDate(0, Month::FEBRUARY, MIN_YEAR), std::invalid_argument);

    REQUIRE_THROWS_AS(CDate(30, Month::FEBRUARY, MIN_YEAR), std::invalid_argument);
}

TEST_CASE("throw exception4")
{
    REQUIRE_THROWS_AS(CDate(MIN_DAY, static_cast<Month>(13), MIN_YEAR), std::invalid_argument);

    REQUIRE_THROWS_AS(CDate(MIN_DAY, static_cast<Month>(0), MIN_YEAR), std::invalid_argument);

    REQUIRE_THROWS_AS(CDate(MIN_DAY, static_cast<Month>(99), MIN_YEAR), std::invalid_argument);
}

TEST_CASE("operator plus prefix")
{
    unsigned expectedDay = MIN_DAY + 1;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::FRIDAY;

    CDate cDate = CDate(MIN_DAY, expectedMonth, expectedYear);
    ++cDate;
    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("operator postprefix")
{
    unsigned expectedDay = MIN_DAY + 1;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::FRIDAY;

    CDate cDate = CDate(MIN_DAY, expectedMonth, expectedYear);
    cDate++;
    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("minus prefix")
{
    unsigned expectedDay = MIN_DAY;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::THURSDAY;

    CDate cDate = CDate(MIN_DAY + 1, expectedMonth, expectedYear);
    --cDate;
    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("minus postfix")
{
    unsigned expectedDay = MIN_DAY;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::THURSDAY;

    CDate cDate = CDate(MIN_DAY + 1, expectedMonth, expectedYear);
    cDate--;
    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("plus days")
{
    unsigned expectedDay = MIN_DAY + 2;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::SATURDAY;

    CDate cDate = CDate(MIN_DAY, expectedMonth, expectedYear);
    CDate cDate1 = cDate + 2;
    REQUIRE(expectedDay == cDate1.GetDay());
    REQUIRE(expectedMonth == cDate1.GetMonth());
    REQUIRE(expectedYear == cDate1.GetYear());
    REQUIRE(expectedWeekDay == cDate1.GetWeekDay());

    CDate cDate2 = 2 + cDate;
    REQUIRE(expectedDay == cDate2.GetDay());
    REQUIRE(expectedMonth == cDate2.GetMonth());
    REQUIRE(expectedYear == cDate2.GetYear());
    REQUIRE(expectedWeekDay == cDate2.GetWeekDay());

    CDate cDate3 = cDate + 0;
    REQUIRE(cDate.GetDay() == cDate3.GetDay());
    REQUIRE(cDate.GetMonth() == cDate3.GetMonth());
    REQUIRE(cDate.GetYear() == cDate3.GetYear());
    REQUIRE(cDate.GetWeekDay() == cDate3.GetWeekDay());

    CDate cDate4 = cDate - 0;
    REQUIRE(cDate.GetDay() == cDate4.GetDay());
    REQUIRE(cDate.GetMonth() == cDate4.GetMonth());
    REQUIRE(cDate.GetYear() == cDate4.GetYear());
    REQUIRE(cDate.GetWeekDay() == cDate4.GetWeekDay());
}

TEST_CASE("minus days")
{
    unsigned expectedDay = MIN_DAY;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::THURSDAY;

    CDate cDate = CDate(MIN_DAY + 2, expectedMonth, expectedYear);
    CDate cDate1 = cDate - 2;
    REQUIRE(expectedDay == cDate1.GetDay());
    REQUIRE(expectedMonth == cDate1.GetMonth());
    REQUIRE(expectedYear == cDate1.GetYear());
    REQUIRE(expectedWeekDay == cDate1.GetWeekDay());


    CDate cDate2 = cDate - 0;
    REQUIRE(cDate.GetDay() == cDate2.GetDay());
    REQUIRE(cDate.GetMonth() == cDate2.GetMonth());
    REQUIRE(cDate.GetYear() == cDate2.GetYear());
    REQUIRE(cDate.GetWeekDay() == cDate2.GetWeekDay());
}

TEST_CASE("minus dates2")
{
    unsigned expectedDay = MIN_DAY;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;

    CDate cDate = CDate(MIN_DAY + 2 , expectedMonth , expectedYear);
    CDate cDate2 = CDate(MIN_DAY + 1 , expectedMonth , expectedYear);
    unsigned resultDays = cDate - cDate2;
    REQUIRE(expectedDay == resultDays);

    resultDays = cDate2 - cDate;
    REQUIRE(expectedDay != resultDays);
}

TEST_CASE("plus equal dates")
{
    unsigned expectedDay = MIN_DAY + 2;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::SATURDAY;

    CDate cDate = CDate(MIN_DAY, expectedMonth, expectedYear);
    cDate += 2;
    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("minus equals")
{
    unsigned expectedDay = MIN_DAY;
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;
    WeekDay expectedWeekDay = WeekDay::THURSDAY;

    CDate cDate = CDate(MIN_DAY + 2, expectedMonth, expectedYear);
    cDate -= 2;
    REQUIRE(expectedDay == cDate.GetDay());
    REQUIRE(expectedMonth == cDate.GetMonth());
    REQUIRE(expectedYear == cDate.GetYear());
    REQUIRE(expectedWeekDay == cDate.GetWeekDay());
}

TEST_CASE("equals compare")
{
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;

    CDate cDate = CDate(MIN_DAY + 2 , expectedMonth , expectedYear);
    CDate cDate1 = CDate(MIN_DAY + 2 , expectedMonth , expectedYear);
    CDate cDate3 = CDate(MIN_DAY + 3 , expectedMonth , expectedYear);

    REQUIRE(cDate == cDate1);
    REQUIRE(cDate1 != cDate3);
}

TEST_CASE("compare less")
{
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;

    CDate cDate = CDate(MIN_DAY + 2 , expectedMonth , expectedYear);
    CDate cDate1 = CDate(MIN_DAY + 3 , expectedMonth , expectedYear);

    REQUIRE(true == cDate < cDate1);
    REQUIRE(false == cDate1 < cDate);
}

TEST_CASE("compare less2")
{
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;

    CDate cDate = CDate(MIN_DAY + 2 , expectedMonth , expectedYear);
    CDate cDate1 = CDate(MIN_DAY + 3 , expectedMonth , expectedYear);

    REQUIRE(false == cDate > cDate1);
    REQUIRE(true == cDate1 > cDate);
}

TEST_CASE("equals")
{
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;

    CDate cDate = CDate(MIN_DAY + 2 , expectedMonth , expectedYear);
    CDate cDate1 = CDate(MIN_DAY + 3 , expectedMonth , expectedYear);
    CDate cDate2 = CDate(MIN_DAY + 3 , expectedMonth , expectedYear);

    REQUIRE(cDate <= cDate1);
    REQUIRE(cDate1 >= cDate);
    REQUIRE(cDate1 <= cDate2);
}

TEST_CASE("compare")
{
    Month expectedMonth = Month::JANUARY;
    int expectedYear = MIN_YEAR;

    CDate cDate = CDate(MIN_DAY + 2, expectedMonth , expectedYear);
    CDate cDate1 = CDate(MIN_DAY + 3 , expectedMonth , expectedYear);
    CDate cDate2 = CDate(MIN_DAY + 3 , expectedMonth , expectedYear);

    REQUIRE(cDate <= cDate1);
    REQUIRE(cDate1 >= cDate);
    REQUIRE(cDate1 >= cDate2);
}

TEST_CASE("compare with date")
{
    CDate date(15, Month::MARCH, 2023);
    std::ostringstream oss;
    oss << date;

    REQUIRE("15:3:2023" == oss.str());
}

TEST_CASE("compare with date2")
{
    std::istringstream iss("25:12:2022");
    CDate date;
    iss >> date;
    REQUIRE(25 == date.GetDay());
    REQUIRE(Month::DECEMBER == date.GetMonth());
    REQUIRE(2022 == date.GetYear());
}

TEST_CASE("compare with date failure")
{
    std::istringstream iss("25:12?2022");
    CDate date;
    iss >> date;
    REQUIRE(iss.bad());
}

TEST_CASE("TEST")
{
    CDate date(11, Month::MAY, 2224);
 
    WeekDay expectedWeekDay = WeekDay::TUESDAY;
    REQUIRE(date.GetWeekDay() == expectedWeekDay);
}
