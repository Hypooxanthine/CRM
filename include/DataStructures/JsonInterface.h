#pragma once

#include <string>
#include <sstream>

#include <QVariant>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include "contact.h"
#include "interaction.h"
#include "todo.h"
#include "contactmanager.h"
#include "interactionmanager.h"
#include "todomanager.h"

class JsonInterface
{
public: // Publics methods

    /**
     * @brief ExportData Has to be called for exporting data
     * @param contactManager references a contact list
     * @param path references the path where the json file will be saved
     */
    static void ExportData(const ContactManager& contactManager, const std::string& path);

private: // Private methods
    /**
     * @brief contact_TO_QJsonObject Has to be called to make a QJsonObject from a contact object
     * @param contact references a contact
     * @return contact's QJsonObject
     */
    static QJsonObject contact_TO_QJsonObject(const Contact& contact);

    /**
     * @brief interaction_TO_QJsonObject Has to be called to make a QJsonObject from an iteration object
     * @param interaction references an interaction
     * @return interaction's QJsonObject
     */
    static QJsonObject interaction_TO_QJsonObject(const Interaction& interaction);

    /**
     * @brief todo_TO_QJsonObject Has to be called to make a QJsonObject from a todo object
     * @param todo references a todo
     * @return todo's QJsonObject
     */
    static QJsonObject todo_TO_QJsonObject(const Todo& todo);

    /**
     * @brief todoList_TO_QJsonArray Has to be called to make a QJsonArray from a todoManager object
     * @param todoManager references a todoManager
     * @return QJsonArray of todo's QJsonObject
     */
    static QJsonArray todoList_TO_QJsonArray(const TodoManager& todoManager);

    /**
     * @brief interactionList_TO_QJsonArray Has to be called to make a QJsonArray from an interactionManager object
     * @param interactionManager references an interactionManager
     * @return QJsonArray of interaction's QJsonObject
     */
    static QJsonArray interactionList_TO_QJsonArray(const InteractionManager& interactionManager);

    /**
     * @brief contactList_TO_QJsonArray Has to be called to make a QJsonArray from an contactManager object
     * @param contactManager references a contactManager
     * @return QJsonArray of contact's QJsonObject
     */
    static QJsonArray contactList_TO_QJsonArray(const ContactManager& contactManager);
};
