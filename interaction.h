#pragma once

#include <string>
#include <vector>

#include "date.h"
#include "todo.h"

class Interaction
{
public: // Publics methods
    Interaction() = delete;
    Interaction(const std::string& content, const Date& date);
    Interaction(const std::string& content);

private: // Private methods
    void parseTodos(const std::string& str);

private: // Private members
    std::string content;
    Date date;
    std::vector<Todo> todos;
};

