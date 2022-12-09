#include "DataStructures/todo.h"

#include <sstream>
#include <iostream>

Todo::Todo(Todo&& other)
    : content(std::move(other.content)), date(std::move(other.date))
{}

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

            if(const auto result = Date::parseDate(dateToken); result.has_value())
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

std::ostream& operator<<(std::ostream& os, const Todo& todo)
{
    os << "(" << todo.getDate() << ") " << todo.getContent();
    return os;
}

bool Todo::operator==(const Todo& other) const
{
    return content == other.content && date == other.date;
}
