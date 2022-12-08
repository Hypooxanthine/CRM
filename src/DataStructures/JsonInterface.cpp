#include "DataStructures/JsonInterface.h"

 void JsonInterface::ExportData(const ContactManager& contactManager, const std::string& path)
{
    QFile file (QString::fromStdString(path)+"\\data.json");
    QJsonObject data{
        {"Data",contactList_TO_QJsonArray(contactManager)}
    };
    QJsonDocument JSONdoc;
    JSONdoc.setObject(data);
    QByteArray bytes = JSONdoc.toJson( QJsonDocument::Indented );

        if (file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ))
        {
            QTextStream iStream( &file );
                    iStream.setCodec( "utf-8" );
                    iStream << bytes;
                    file.close();
        }
        else
        {
            std::cout << "file open failed: " << path << std::endl;
        }
}

QJsonArray JsonInterface::contactList_TO_QJsonArray(const ContactManager& contactManager)
{
    QJsonArray contactList_QJsonArray;
    if(!contactManager.isEmpty())
    {
        for(auto iteratorContact=contactManager.begin();
            (iteratorContact != contactManager.end());
            iteratorContact++)
        {
            contactList_QJsonArray.push_back(contact_TO_QJsonObject(*iteratorContact));
        }
        return contactList_QJsonArray;
    }
    else
    {
        contactList_QJsonArray.push_back(" no contact ! ");
        return contactList_QJsonArray;
    }
}

QJsonObject JsonInterface::contact_TO_QJsonObject(const Contact& contact)
{
    std::stringstream idContact, dateContact;
    idContact << contact.getId() ;
    dateContact << contact.getDate();
    QJsonObject contact_jsonObj
    {
        {"idContat", QString::fromStdString(idContact.str())},
        {"Name", QString::fromStdString(contact.getName())},
        {"email", QString::fromStdString(contact.getEmail())},
        {"phone", QString::fromStdString(contact.getPhone())},
        {"photoPath", QString::fromStdString(contact.getPhotoPath())},
        {"creationDate",  QString::fromStdString(dateContact.str())},
        {"interactionList", interactionList_TO_QJsonArray(contact.getInteractionManager())}
    };
    return contact_jsonObj;
}

QJsonArray JsonInterface::interactionList_TO_QJsonArray(const InteractionManager& interactionManager)
{
    QJsonArray interactionList_QJsonArray;
    if(!interactionManager.isEmpty())
    {
        for(auto iteratorInteraction=interactionManager.begin();
            (iteratorInteraction != interactionManager.end());
            iteratorInteraction++)
        {
            interactionList_QJsonArray.push_back(interaction_TO_QJsonObject(*iteratorInteraction));
        }
        return interactionList_QJsonArray;
    }
    else
    {
        interactionList_QJsonArray.push_back(" no interaction ! ");
        return interactionList_QJsonArray;
    }
}

QJsonObject JsonInterface::interaction_TO_QJsonObject(const Interaction& interaction)
{
    std::stringstream dateInteraction;
    dateInteraction << interaction.getDate();
    QJsonObject interaction_jsonObj
    {
        {"content", QString::fromStdString(interaction.getContent())},
        {"Date",  QString::fromStdString(dateInteraction.str())},
        {"todoList", todoList_TO_QJsonArray(interaction.getTodos())}
    };
    return interaction_jsonObj;
}

QJsonArray JsonInterface::todoList_TO_QJsonArray(const TodoManager& todoManager)
{
    QJsonArray todoList_QJsonArray;
    if(!todoManager.isEmpty())
    {
        int i = 0;
        for(auto iteratorTodo=todoManager.begin();
            (iteratorTodo != todoManager.end());
            iteratorTodo++)
        {
            todoList_QJsonArray.push_back(todo_TO_QJsonObject(*iteratorTodo));
            i++;
        }
        return todoList_QJsonArray;
    }
    else
    {
        todoList_QJsonArray.push_back(" no todo ! ");
        return todoList_QJsonArray;
    }
}

QJsonObject JsonInterface::todo_TO_QJsonObject(const Todo& todo)
{
    std::stringstream dateTodo;
    dateTodo << todo.getDate();
    QJsonObject todo_jsonObj
    {
        {"content", QString::fromStdString(todo.getContent())},
        {"Date",  QString::fromStdString(dateTodo.str())}
    };
    return todo_jsonObj;
}

