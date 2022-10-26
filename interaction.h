#pragma once

#include <string>
#include <todomanager.h>

#include "date.h"
#include "todo.h"

class Interaction
{
public: // Publics methods
    friend class UnitTest;
    /**
     * @brief Default constructor is deleted.
     */
    Interaction() = delete;

    /**
     * @brief Has to be called for a known Interaction. For example, when retrieving an Interaction from the database, the Interaction
     * is known, so is the date.
     * @param content The content of the Interaction. It shouldn't contain any \@todo.
     * @param date The date the Interaction was created.
     */
    Interaction(const std::string& content, const Date& date);

    /**
     * @brief Has to be called for a new Interaction. It'll parse all the todos from it.
     * @param content The content of the Interaction. Every \@todo's won't appear in the content after parsing : they will be part of
     * the Todo vector.
     */
    Interaction(const std::string& content);

    // Setters
    /**
     * @brief Sets the content of the interaction. No \@todo should appear in it.
     * @param str The new content string.
     */
    inline void setContent(const std::string& str) { content = str; }

    /**
     * @brief Sets the Date of the content.
     * @param d The new Date.
     */
    inline void setDate(const Date d) { date = d; }

    /**
     * @brief Sets the Todo's list.
     * @param t The new Todo's list.
     */
    inline void setTodos(const TodoManager& t) { todos = t;}

    // Getters
    /**
     * @brief Gets the content of the Interaction. It shouldn't contain any \@todo.
     * @return The content of the Interaction.
     */
    inline const std::string& getContent() const { return content; }

    /**
     * @brief Gets the creation Date of the Interaction.
     * @return The creation Date of the Interaction.
     */
    inline const Date& getDate() const { return date; }

    /**
     * @brief Gets the Todo's list.
     * @return The Todo's list.
     */
    inline const TodoManager& getTodos() const { return todos; }

    Interaction& operator=(const Interaction&) = default;
    friend std::ostream& operator<<(std::ostream& os, const Interaction& interaction);

private: // Private methods
    /**
     * @brief This method parses all the Todo's and puts them into the Todo's list.
     * @param str The raw content string of the Interaction, as it is at the creation.
     */
    void parseTodos(const std::string& str);

private: // Private members
    std::string content;
    Date date;
    TodoManager todos;
};
;
