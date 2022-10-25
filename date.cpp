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
