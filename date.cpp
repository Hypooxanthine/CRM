#include "date.h"

Date::Date(const uint8_t& day, const uint8_t& month, const uint16_t& year)
    : day(day), month(month), year(year)
{}

Date::Date()
    : Date(0, 0, 0)
{}

Date Date::today()
{
    const date::year_month_day asDateLib{date::floor<date::days>(std::chrono::system_clock::now())};
    // Using explicit conversion operators from date::year_mont_day to retrieve the values of day, month & year.
    return Date((unsigned)asDateLib.day(), (unsigned)asDateLib.month(), std::abs((int)asDateLib.year()));
}

Date::operator std::string() const
{
    std::ostringstream ss;

    if(day < 10) ss << "0";
    ss << +day << "/";

    if(month < 10) ss << "0";
    ss << +month << "/";

    ss << +year;

    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << (std::string)date;
    return os;
}

bool Date::operator==(const Date& other) const
{
    return day == other.day && month == other.month && year == other.year;
}
