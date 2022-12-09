#pragma once

#include "DataStructures/contactmanager.h"

#include <QtSql/QSqlDatabase>

class DBInterface
{
public: // Public methods

    /**
     * @brief Intializes the DBInterface. If database does not exist, it'll create it.
     */
    static void Init();

    /**
     * @brief Loads data from the database. Returns an empty ContactManager if anything is going wrong.
     * @warning This function asserts the DBInterface was initialized.
     * @see DBInterface::Init().
     * @return A ContactManager with all the Contacts, and all their depending Interactions and Todos.
     */
    static ContactManager LoadData();

    /**
     * @brief Saves data into the database.
     * @warning This function asserts the DBInterface was initialized.
     * @see DBInterface::Init().
     * @param contacts A const refence to the list of contacts.
     * @return true on success; otherwise returns false.
     */
    static bool SaveData(const ContactManager& contacts);

private: // Private methods

    /**
     * @brief Executes a query and print debug messages if something goes wrong.
     * @param q A reference to the QSqlQuery to execute.
     * @return true on success; otherwise returns false.
     */
    static bool TestQuery(QSqlQuery& q);

    /**
     * @brief TestQuery
     * @param q A QSqlQuery rvalue.
     * @return true on success; otherwise returns false.
     */
    static bool TestQuery(QSqlQuery&& q);

    /**
     * @brief Gets the last registered auto increment value of a data table.
     * @param tableName A const reference to the table name string.
     * @return The last registered auto increment value.
     */
    static std::optional<int> GetLastTableID(const std::string& tableName);

private: // Private members
    static QSqlDatabase db;
};
