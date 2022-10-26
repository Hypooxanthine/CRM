#pragma once

#include "datelib.h"


class Date
{
public:
    friend class UnitTest;
    /**
     * @brief Creates an "invalid" date : day, month and year are set to zero.
     */
    Date();

    Date(Date&&) = default;
    Date(const Date&) = default;

    /**
     * @brief Creates a new date. No verification is done about the values, leap years, etc.
     * @param day Day value.
     * @param month Month value.
     * @param year Year value.
     */
    Date(const uint8_t& day, const uint8_t& month, const uint16_t& year);

    /**
     * @brief Gets the day value.
     * @return The day of the Date.
     */
    inline const uint8_t& getDay() const { return day; }

    /**
     * @brief Gets the month value.
     * @return The month of the Date.
     */
    inline const uint8_t& getMonth() const { return month; }

    /**
     * @brief Gets the year value.
     * @return The year of the Date.
     */
    inline const uint16_t& getYear() const { return year; }

    /**
     * @brief Sets the day of the Date.
     * @param d The new day value.
     */
    inline void setDay(const uint8_t& d) { day = d; }

    /**
     * @brief Sets the month of the Date.
     * @param m The new month value.
     */
    inline void setMonth(const uint8_t& m) { month = m; }

    /**
     * @brief Sets the year of the Date.
     * @param y The new year value.
     */
    inline void setYear(const uint16_t& y) { year = y ;}

    /**
     * @brief Gets the current date.
     * @return An instance of Date pointing to the current date according to the operating system.
     */
    static Date today();

    Date& operator=(const Date&) = default;

    friend std::ostream& operator<<(std::ostream& os, const Date& date);

    bool operator==(const Date& other) const;

private:
    uint8_t day, month;
    uint16_t year;
};
