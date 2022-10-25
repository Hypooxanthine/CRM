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


void Interaction::setContent(const std::string& content){ this->content = content;}
void Interaction::setDate(const Date date){this->date = date ;}
void Interaction::setTodos(const std::vector<Todo> &newTodoList ){this->todos = newTodoList;}

std::string Interaction::getContent() const{return this->content;}
Date Interaction::getDate() const{return this->date;}
std::vector<Todo> Interaction::getTodos() const{ return this->todos;}




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
