#pragma once

#include "datelib.h"


class Date
{
public:
    Date();
    Date(const uint8_t& day, const uint8_t& month, const uint16_t& year);

    inline const uint8_t& getDay() const { return day; }
    inline const uint8_t& getMonth() const { return month; }
    inline const uint16_t& getYear() const { return year; }

    inline void setDay(const uint8_t& d) { day = d; }
    inline void setMonth(const uint8_t& m) { month = m; }
    inline void setYear(const uint16_t& y) { year = y ;}

    static Date today();

private:
    uint8_t day, month;
    uint16_t year;
};
