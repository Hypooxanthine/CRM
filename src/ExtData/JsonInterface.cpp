#include "ExtData/JsonInterface.h"

#define JSONFILE_DIRECTORY "./Data/"
#define JSONFILE_NAME "data.json"
#define JSONFILE_PATH JSONFILE_DIRECTORY JSONFILE_NAME

//*/////////////////////////////////////////////////////////////
//Useful public methods to import data from json file
//*/////////////////////////////////////////////////////////////
ContactManager JsonInterface::ImportData()
{
    return ImportData(JSONFILE_PATH);
}

ContactManager JsonInterface::ImportData(QString path)
{
    ContactManager contactManager;
    QFile file (path);
    //couldn't open json file return an empy ContactManager.
    if(! file.open( QIODevice::ReadOnly))
        return contactManager;
    QByteArray bytes = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument JSONdoc = QJsonDocument::fromJson( bytes, &jsonError );

    if( jsonError.error != QJsonParseError::NoError )
            {
                std::cout << "fromJson failed: " << jsonError.errorString().toStdString() << std::endl;
                return contactManager;
            }
            if( JSONdoc.isObject())
            {
                QJsonObject data = JSONdoc.object();
                QJsonArray contactList = data.value("Data").toArray();
                contactManager = contactListQJsonArray_TO_contactList(contactList);
            }
    return contactManager;
}

//*/////////////////////////////////////////////////////////////
//Useful public methods to export data from json file
//*/////////////////////////////////////////////////////////////
void JsonInterface::ExportData(const ContactManager& contactManager)
{
     ExportData(contactManager, JSONFILE_PATH);
}

void JsonInterface::ExportData(const ContactManager& contactManager, QString path)
{
    QFile file (path);
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
            std::cout << "file open failed: " << JSONFILE_NAME << std::endl;
        }
}

//*///////////////////////////////////////////////////////////////////
//Useful private methods to export data from json file
//*///////////////////////////////////////////////////////////////////
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
        return contactList_QJsonArray;
    }
}

QJsonObject JsonInterface::contact_TO_QJsonObject(const Contact& contact)
{
    QJsonObject contact_jsonObj
    {
        {"FirstName", QString::fromStdString(contact.getFirstName())},
        {"LastName", QString::fromStdString(contact.getLastName())},
        {"Company", QString::fromStdString(contact.getCompany())},
        {"email", QString::fromStdString(contact.getEmail())},
        {"phone", QString::fromStdString(contact.getPhone())},
        {"photoPath", QString::fromStdString(contact.getPhotoPath())},
        {"creationDate",  QString::fromStdString(static_cast<std::string>(contact.getDate()))},
        {"lastEdit",  QString::fromStdString(static_cast<std::string>(contact.getLastEditDate()))},
        {"interactionList", interactionList_TO_QJsonArray(contact.getInteractions())}
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
        return interactionList_QJsonArray;
    }
}

QJsonObject JsonInterface::interaction_TO_QJsonObject(const Interaction& interaction)
{
    QJsonObject interaction_jsonObj
    {
        {"content", QString::fromStdString(interaction.getContent())},
        {"Date",  QString::fromStdString(static_cast<std::string>(interaction.getDate()))},
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
        return todoList_QJsonArray;
    }
}

QJsonObject JsonInterface::todo_TO_QJsonObject(const Todo& todo)
{
    QJsonObject todo_jsonObj
    {
        {"content", QString::fromStdString(todo.getContent())},
        {"Date",  QString::fromStdString(static_cast<std::string>(todo.getDate()))}
    };
    return todo_jsonObj;
}

//*///////////////////////////////////////////////////////////////////
//Useful private methods to import data from json file
//*///////////////////////////////////////////////////////////////////
ContactManager JsonInterface::contactListQJsonArray_TO_contactList(const QJsonArray& contactList)
{
    ContactManager contactManager;
    for (int j = 0; j <contactList.size(); j++)
    {
        QJsonObject contactQJsonObject = contactList.at(j).toObject();
        Contact contact = contactQJsonObject_TO_contact(contactQJsonObject);
        contactManager.add(contact);
    }
    return contactManager;
}

Contact JsonInterface::contactQJsonObject_TO_contact(const QJsonObject& object)
{
    std::string firstName = object.value("FirstName").toString().toStdString();
    std::string lastName = object.value("LastName").toString().toStdString();
    std::string company = object.value("Company").toString().toStdString();
    std::string email = object.value("email").toString().toStdString();
    std::string phone = object.value("phone").toString().toStdString();
    std::string photoPath = object.value("photoPath").toString().toStdString();
    std::string creationDate = object.value("creationDate").toString().toStdString();
    std::string lastEdit = object.value("lastEdit").toString().toStdString();

    Contact contact = Contact(  firstName, lastName,
                                company, email,
                                phone, photoPath,
                                Date::parseDate(creationDate).value(),
                                Date::parseDate(lastEdit).value() );

    QJsonArray interactionList = object.value("interactionList").toArray();
    InteractionManager interactionManager = interactionListQJsonArray_TO_interactionList(interactionList);
    contact.setInteractionManager( interactionManager);

    return contact;
}

InteractionManager JsonInterface::interactionListQJsonArray_TO_interactionList(const QJsonArray& interactionList)
{
    InteractionManager interactionManager;
    for (int j = 0; j <interactionList.size(); j++)
    {
        QJsonObject interactionQJsonObject = interactionList.at(j).toObject();
        Interaction interaction = interactionQJsonObject_TO_interaction(interactionQJsonObject);
        interactionManager.add(interaction);
    }
    return interactionManager;
}

Interaction JsonInterface::interactionQJsonObject_TO_interaction(const QJsonObject& object)
{
    std::string content = object.value("content").toString().toStdString();
    std::string date = object.value("Date").toString().toStdString();

    Interaction interaction = Interaction(content,Date::parseDate(date).value());

    QJsonArray todoList = object.value("todoList").toArray();
    TodoManager todoManager = todoListQJsonArray_TO_todoList(todoList);
    interaction.setTodos(todoManager);

    return interaction;
}

TodoManager JsonInterface::todoListQJsonArray_TO_todoList(const QJsonArray& todoList)
{
    TodoManager tododManager;
      for (int j = 0; j <todoList.size(); j++)
      {
          QJsonObject todoQJsonObject = todoList.at(j).toObject();
          Todo todo = todoQJsonObject_TO_todo(todoQJsonObject);
          tododManager.add(todo);
      }
    return tododManager;
}

Todo JsonInterface::todoQJsonObject_TO_todo(const QJsonObject& object)
{
    std::string content = object.value("content").toString().toStdString();
    std::string date = object.value("Date").toString().toStdString();

    return Todo(content,Date::parseDate(date).value());
}
