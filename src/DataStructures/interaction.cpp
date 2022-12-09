#include "DataStructures/interaction.h"

#include <sstream>
#include <string>

Interaction::Interaction(const std::string& content, const Date& date)
    : content(content), date(date)
{}

Interaction::Interaction(const std::string& content)
{
    parseTodos(content);
    date = Date::today();
}

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
            todos.add(Todo(todoContent));
        }
        else
            content += line + '\n';
    }

    // Right trim of the content
    content.erase(std::find_if(content.rbegin(), content.rend(), [](const char& c){ return c != '\n';}).base(), content.end());
}



std::ostream& operator<<(std::ostream& os, const Interaction& interaction)
{
    os << "Content : \"" << interaction.getContent() << "\"" << std::endl;
    os << "Date : " << interaction.getDate() << std::endl;

    if(interaction.getTodos().isEmpty())
        os << "No Todo.";
    else
    {
        os << "Todo's :" << std::endl;
        os << interaction.getTodos();
    }

    return os;
}

bool Interaction::operator==(const Interaction& other) const
{
    return content == other.content
            && date == other.date
            && todos == other.todos;
}
