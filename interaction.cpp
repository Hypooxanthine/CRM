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
    std::istringstream ss(str);

    std::string line;

    // Working on every line of the raw content string.
    while(std::getline(ss, line))
    {
        std::istringstream liness(line);
        std::string word;

        liness >> word; // The first word of the line is stored in word.

        if(word == "@todo")
        {
            std::string todoContent = line.substr(liness.tellg()); // Contains the string except "@todo"
            todos.push_back(Todo(todoContent));
        }
        else
            content += line + '\n';

    }
}

std::ostream& operator<<(std::ostream& os, const Interaction& interaction)
{
    os << "Content : \"" << interaction.getContent() << "\"" << std::endl;
    os << "Date : " << interaction.getDate() << std::endl;

    if(interaction.getTodos().empty())
        os << "No Todo.";
    else
    {
        os << "Todo's :";

        for(const auto& todo : interaction.getTodos())
        {
            os << std::endl << "\t" << todo;
        }
    }

    return os;
}
