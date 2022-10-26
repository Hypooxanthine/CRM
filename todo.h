#pragma once

#include <string>
#include <optional>

#include "date.h"

class Todo
{
public:
    friend class UnitTest;
    /**
     * @brief Defautl constructor is deleted.
     */
    Todo() = delete;

    /**
     * @brief Has to be called for a known Todo. For example, when retrieving a Todo from the database, the Todo is already known, so is the date.
     * @param content The content of the Todo. It shouldn't contain any \@date tag.
     * @param date The date the Todo has to be done.
     */
    Todo(const std::string& content, const Date& date);

    /**
     * @brief Has to be called for a new Todo. It'll parse the date from it, if any.
     * @param content The raw content of the Todo. A \@date won't appear in it after parsing : it will be in a separated member variable.
     */
    Todo(const std::string& content);


    // Setters
    /**
     * @brief Sets the content of the Todo. It shouldn't contain any \@date tag.
     * @param str The new content of the Todo.
     */
    inline void setContent(const std::string &str) { content = str; }

    /**
     * @brief Sets the Date of the todo, i.e the date the todo has to be done.
     * @param d The new Date of the Todo.
     */
    inline void setDate(const Date d) { date = d; }

    // Getters
    /**
     * @brief Gets the content of the Todo. It shouldn't contain any \@date tag.
     * @return The content of the Todo.
     */
    const std::string& getContent() const { return content; }

    /**
     * @brief Gets the Date of the Todo.
     * @return The Date of the Todo.
     */
    const Date& getDate() const { return date; }

    friend std::ostream& operator<<(std::ostream& os, const Todo& todo);

private:
    /**
     * @brief Will clear the raw content string from \@date tag, if any. It will be stored in content member variable, and the date (if any)
     * will be stored in date member variable. If no date, the current date will be used.
     * @param str The raw content data of the Todo.
     */
    void getContentAndDate(const std::string& str);

    /**
     * @brief Will try to parse a date from a string, according to the format : dd/mm/yyy.
     * @param str The raw date string.
     * @return An optional Date : empty if parsing failed.
     */
    static std::optional<Date> parseDate(const std::string& str);

    /**
     * @brief parseNumber
     * @param str
     * @return
     */
    static std::optional<uint16_t> parseNumber(const std::string& str);

private:
    std::string content;
    Date date;
};


