#include "todo.h"

#include <sstream>

Todo::Todo(const std::string& content, const Date& date)
    : content(content), date(date)
{}

Todo::Todo(const std::string& content)
{
    getContentAndDate(content);
}

void Todo::setContent(const std::string& content){ this->content = content;}
void Todo::setDate(const Date date){this->date = date ;}

std::string Todo::getContent() const{return this->content;}
Date Todo::getDate() const{return this->date;}



void Todo::getContentAndDate(const std::string& str)
{
    std::istringstream ss(str);
    std::string word;

    bool dateFound = false;

    do
    {
        ss >> word;

        if(!dateFound && word == "@date")
        {
            std::string dateToken;
            ss >> dateToken;

            if(ss.tellg() == std::istringstream::eofbit) break;

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
    } while(ss.tellg() != std::istringstream::eofbit);

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

std::optional<int> Todo::parseNumber(const std::string& str)
{

}
