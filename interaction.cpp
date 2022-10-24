#include "interaction.h"

#include <sstream>
#include <string>

Interaction::Interaction(const std::string& content, const Date& date)
    : date(date)
{
    parseTodos(content);
}

Interaction::Interaction(const std::string& content)
    : Interaction(content, Date::today())
{}

void Interaction::parseTodos(const std::string& str)
{
    std::stringstream ss(str);

    std::string line;

    while(std::getline(ss, line))
    {
        std::stringstream liness(line);
        std::string word;

        liness >> word;

        if(word == "@todo")
        {
            std::string todoContent = line.substr(liness.tellg());
            todos.push_back(Todo(todoContent));
        }
        else
            content += line + '\n';

    }
}
