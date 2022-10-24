#include "todo.h"

#include <sstream>

Todo::Todo(const std::string& content, const Date& date)
    : content(content), date(date)
{}

Todo::Todo(const std::string& content)
{
    getContentAndDate(content);
}

void Todo::getContentAndDate(const std::string& str)
{
    std::stringstream ss(str);
    std::string word;

    bool dateFound = false;

    do
    {
        ss >> word;

        if(!dateFound && word == "@date")
        {
            std::string dateToken;
            ss >> dateToken;

            if(ss.tellg() == std::stringstream::eofbit) break;

            const auto result = parseDate(dateToken);

            if(result)
            {
                dateFound = true;
                date = result.value();
            }
            else
            {
                content += word;
            }
        }
        else
            content += word;
    } while(ss.tellg() != std::stringstream::eofbit);

    if(!dateFound)
        date = Date::today();
}

std::optional<Date> Todo::parseDate(const std::string& str)
{
    std::optional<Date> out;

    bool dayFound = false, monthFound = false, yearFound = false, error = false;
    uint8_t day = 0, month = 0;
    uint16_t year = 0;

    std::stringstream ss(str);
    std::string token;

    while(std::getline(ss, token, '/'))
    {
        if(!dayFound)
        {
            if(auto number = parseNumber(token); number.has_value())
            {
                dayFound = true;
                day = number.value();
            }
            else
                break;
        }
        else if(!monthFound)
        {
            if(auto number = parseNumber(token); number.has_value())
            {
                monthFound = true;
                month = number.value();
            }
            else
                break;
        }
        else if(!yearFound)
        {
            if(auto number = parseNumber(token); number.has_value())
            {
                yearFound = true;
                year = number.value();
            }
            else
                break;
        }
        else // Every number has been found but there is another token : the date is not valid
        {
            error = true;
            break;
        }

    }

    if(!error && dayFound && monthFound && yearFound)
        out = Date(day, month, year);

    return out;
}

std::optional<int> Todo::parseNumber(const std::string& str)
{

}
