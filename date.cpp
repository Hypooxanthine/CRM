#include "date.h"

Date::Date(const uint8_t& day, const uint8_t& month, const uint16_t& year)
    : day(day), month(month), year(year)
{}

Date::Date()
    : Date(0, 0, 0)
{}

Date Date::today()
{
    const auto asDateLib = date::year_month_day{date::floor<date::days>(std::chrono::system_clock::now())};
    return Date((unsigned)asDateLib.day(), (unsigned)asDateLib.month(), std::abs((int)asDateLib.year()));
}
