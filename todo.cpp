#include "todo.h"

#include <sstream>
#include <iostream>

Todo::Todo(const std::string& content, const Date& date)
    : content(content), date(date)
{}

Todo::Todo(const std::string& content)
{
    getContentAndDate(content);
}

void Todo::getContentAndDate(const std::string& str)
{
    std::istringstream ss(str);
    // We only need the first line
    std::string firstLine;
    std::getline(ss, firstLine);
    ss = std::istringstream(firstLine);

    std::string word;

    bool dateFound = false;

    while(std::getline(ss, word, ' ')) // For each word
    {
        if(!dateFound && word == "@date")
        {
            std::string dateToken;
            if(ss.eof()) // If there isn't anything after "@date", there isn't any date to parse, so we break.
            {
                content += word; // We add the word "@date" to the content so the user can see there was a problem in his typing.
                break;
            }

            ss >> dateToken;

            if(const auto result = parseDate(dateToken); result.has_value())
            {
                dateFound = true;
                date = result.value();
            }
            else
            {
                // Example : user typed @date 11/12/a
                // We will add "@date 11/12/a" to the content so the user can see there was a
                // probleme in his typing.
                // Another @date tag can be considered.
                content += word;
                content += ' ';
                content += dateToken;
            }
        }
        else
            content += word + ' ';
    }

    // Right trim of the content
    content.erase(std::find_if(content.rbegin(), content.rend(), [](const char& c){ return c != ' ';}).base(), content.end());
    // Left trim of the content
    content.erase(content.begin(), std::find_if(content.begin(), content.end(), [](const char& c){ return c != ' ';}));

    if(!dateFound)
        date = Date::today();
}

std::optional<Date> Todo::parseDate(const std::string& str)
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

std::optional<uint16_t> Todo::parseNumber(const std::string& str)
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

std::ostream& operator<<(std::ostream& os, const Todo& todo)
{
    os << "(" << todo.getDate() << ") " << todo.getContent();
    return os;
}
