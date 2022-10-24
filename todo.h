#pragma once

#include <string>
#include <optional>

#include "date.h"

class Todo
{
public:
    Todo() = delete;
    Todo(const std::string& content, const Date& date);
    Todo(const std::string& content);

private:
    void getContentAndDate(const std::string& str);
    std::optional<Date> parseDate(const std::string& str);
    std::optional<int> parseNumber(const std::string& str);

private:
    std::string content;
    Date date;
};
