#pragma once

#include "Date/date.h"

#include <optional>

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

    // Getters

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

    // Setters

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

    // Static functions

    /**
     * @brief Gets the current date.
     * @return An instance of Date pointing to the current date according to the operating system.
     */
    static Date today();

    /**
     * @brief Will try to parse a date from a string, according to the format : dd/mm/yyy.
     * @param str The raw date string.
     * @return An optional Date : empty if parsing failed.
     */
    static std::optional<Date> parseDate(const std::string& str);

    /**
     * @brief parseNumber Will try to parse a whole positive number from a string. Max value : 2¹⁶ - 1
     * @param str The raw number string.
     * @return An optional uint16_t : empty if parsing failed.
     */
    static std::optional<uint16_t> parseNumber(const std::string& str);

    Date& operator=(const Date&) = default;

    /**
     * @brief Explicit conversion to a std::string. Days and months will be displayed as two characters, no modification will be done
     * on the year.
     */
    explicit operator std::string() const;

    friend std::ostream& operator<<(std::ostream& os, const Date& date);

    /**
     * @brief Compare operator.
     * @param other The Date to compare to.
     * @return A boolean. True : days, months and years are the same. False otherwise.
     */
    bool operator==(const Date& other) const;

private:
    uint8_t day, month;
    uint16_t year;
};
