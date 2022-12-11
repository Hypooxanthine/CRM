#include "DataStructures/date.h"

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

std::optional<Date> Date::parseDate(const std::string& str)
{
    std::optional<Date> out;

    bool dayFound = false, monthFound = false, yearFound = false;
    bool error = false;

    uint8_t day = 0, month = 0;
    uint16_t year = 0;

    std::istringstream ss(str);
    std::string token;

    while(!error && std::getline(ss, token, '/'))
    {
        if(!dayFound)
        {
            if(auto number = parseNumber(token); number.has_value())
            {
                dayFound = true;
                day = number.value();
            }
            else
                error = true;
        }
        else if(!monthFound)
        {
            if(auto number = parseNumber(token); number.has_value())
            {
                monthFound = true;
                month = number.value();
            }
            else
                error = true;
        }
        else if(!yearFound)
        {
            if(auto number = parseNumber(token); number.has_value())
            {
                yearFound = true;
                year = number.value();
            }
            else
                error = true;
        }
        else // Every number has been found but there is another token : the date is not valid
            error = true;

    }

    if(!error && dayFound && monthFound && yearFound)
        out = Date(day, month, year);

    return out;
}

std::optional<uint16_t> Date::parseNumber(const std::string& str)
{
    std::optional<uint16_t> out;
    uint16_t value = 0;
    uint8_t tenPower = 0;
    bool error = false;

    for(auto it = str.rbegin(); it < str.rend() && !error; it++) // 10000 is the max value for day, month and year.
    {
        if (*it < '0' || *it > '9' || value > 10000) // Only numbers, no '-' : no negative numbers.
            error = true;
        else
            value += (*it - '0') * std::pow(10, tenPower++);
    }

    if(!error) out = value;

    return out;
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

bool Date::operator<(const Date& other) const
{
    if(year < other.year) return true;

    if(year == other.year)
    {
        if(month < other.month) return true;

        if(month == other.month && day < other.day) return true;
    }

    return false;
}

bool Date::operator>(const Date& other) const
{
    return other < *this;
}

bool Date::operator<=(const Date& other) const
{
    return *this == other || *this < other;
}

bool Date::operator>=(const Date& other) const
{
    return *this == other || *this > other;
}
