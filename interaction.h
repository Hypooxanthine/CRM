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


    //getters and setters
    void setContent(const std::string &content);
    void setDate(const Date date);
    void setTodos(const std::vector<Todo> &newTodoList );


    std::string getContent() const;
    Date getDate() const;
    std::vector<Todo> getTodos() const;


private: // Private methods
    void parseTodos(const std::string& str);

private: // Private members
    std::string content;
    Date date;
    std::vector<Todo> todos;
};

