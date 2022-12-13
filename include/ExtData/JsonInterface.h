#pragma once

#include <string>
#include <sstream>

#include <QVariant>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>


#include "DataStructures/contact.h"
#include "DataStructures/interaction.h"
#include "DataStructures/todo.h"
#include "DataStructures/contactmanager.h"
#include "DataStructures/interactionmanager.h"
#include "DataStructures/todomanager.h"

class JsonInterface
{
public: // Publics methods

    /**
     * @brief ExportData Has to be called for exporting data to json file
     * @param contactManager references a ContactManager with all the Contacts, and all their depending Interactions and Todos
     * @param path of the json file
     */
    static void ExportData(const ContactManager& contactManager, QString path);

    /**
     * @brief ExportData Has to be called for exporting data to json file at "./Data/data.son"
     * @param contactManager references a ContactManager with all the Contacts, and all their depending Interactions and Todos
     */
    static void ExportData(const ContactManager& contactManager);

    /**
     * @brief ImportData Has to be called for importing data from json file
     * @param path of the json file
     * @return A ContactManager with all the Contacts, and all their depending Interactions and Todos
     */
    static ContactManager ImportData(QString path);

    /**
     * @brief ImportData Has to be called for importing data from json file at "./Data/data.son"
     * @return A ContactManager with all the Contacts, and all their depending Interactions and Todos
     */
    static ContactManager ImportData();

private: // Private methods
    //useful private methods for exporting data from json file
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

    //useful private methods for importing data from json file
    /**
     * @brief contactQJsonObject_TO_contact Has to be called to make a Contact from a QJsonObject
     * @param references to a QJsonObject
     * @return a Contact object
     */
    static Contact contactQJsonObject_TO_contact(const QJsonObject&);

    /**
     * @brief interactionQJsonObject_TO_interaction Has to be called to make a Interaction from a QJsonObject
     * @param references to a QJsonObject
     * @return an Interaction object
     */
    static Interaction interactionQJsonObject_TO_interaction(const QJsonObject&);

    /**
     * @brief todoQJsonObject_TO_todo Has to be called to make a Todo from a QJsonObject
     * @param references to a QJsonObject
     * @return a Todo object
     */
    static Todo todoQJsonObject_TO_todo(const QJsonObject&);

    /**
     * @brief todoListeQJsonArray_TO_todoList Has to be called to make a TodoManager from a QJsonArray
     * @param references to a QJsonArray
     * @return a TodoManager object
     */
    static TodoManager todoListQJsonArray_TO_todoList(const QJsonArray&);

    /**
     * @brief interactionListeQJsonArray_TO_interactionList Has to be called to make a InteractionManager from a QJsonArray
     * @param references to a QJsonArray
     * @return an InteractionManager object
     */
    static InteractionManager interactionListQJsonArray_TO_interactionList(const QJsonArray&);

    /**
     * @brief contactListQJsonArray_TO_contactList Has to be called to make a ContactManager from a QJsonObject
     * @return a ContactManager object
     */
    static ContactManager contactListQJsonArray_TO_contactList(const QJsonArray&);



};
