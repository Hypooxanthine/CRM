#include "ExtData/dbinterface.h"

#include <optional>

#include <qdebug.h>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QFile>
#include <QDir>

#define DATABASE_DIRECTORY "./Data/"
#define DATABASE_NAME "data.db"
#define DATABASE_PATH DATABASE_DIRECTORY DATABASE_NAME

// Static members definition
QSqlDatabase DBInterface::db = QSqlDatabase::addDatabase("QSQLITE");

void DBInterface::Init()
{
    db.setDatabaseName(DATABASE_PATH);

    // If the database does not exist, we create it.
    if(!QFile::exists(DATABASE_PATH))
    {
        // We create its folder
        if(!QDir().exists(DATABASE_DIRECTORY))
            QDir().mkdir(DATABASE_DIRECTORY);

        db.open();
        QSqlQuery querry;
            querry.prepare("CREATE TABLE 'Contact' ("
                           "'cID'	INTEGER NOT NULL,"
                           "'FirstName'	TEXT NOT NULL,"
                           "'LastName'	TEXT NOT NULL,"
                           "'Company'	TEXT NOT NULL,"
                           "'Email'	TEXT NOT NULL,"
                           "'Phone'	TEXT NOT NULL,"
                           "'PhotoPath'	TEXT,"
                           "'CreationDate'	TEXT NOT NULL,"
                           "UNIQUE('Phone'),"
                           "UNIQUE('Email'),"
                           "PRIMARY KEY('cID' AUTOINCREMENT),"
                           "UNIQUE('PhotoPath')"
                           ")");
            querry.exec();

        querry.clear();
            querry.prepare("CREATE TABLE 'Interaction' ("
                           "'iID'	INTEGER NOT NULL,"
                           "'cID'	INTEGER NOT NULL,"
                           "'Content'	TEXT,"
                           "'CreationDate'	TEXT NOT NULL,"
                           "PRIMARY KEY('iID' AUTOINCREMENT),"
                           "FOREIGN KEY('cID') REFERENCES 'Contact'('cID') ON DELETE CASCADE"
                           ")");
            querry.exec();

        querry.clear();
            querry.prepare("CREATE TABLE 'Todo' ("
                           "'tID'	INTEGER NOT NULL,"
                           "'iID'	INTEGER NOT NULL,"
                           "'Content'	INTEGER,"
                           "'Date'	INTEGER,"
                           "FOREIGN KEY('iID') REFERENCES 'Interaction'('iID'),"
                           "PRIMARY KEY('tID' AUTOINCREMENT)"
                           ")");
            querry.exec();

        db.close();
    }
}

ContactManager DBInterface::LoadData()
{
    // Couldn't open database : we return an empty ContactManager.
    if(!db.open())
        return ContactManager();

    // Getting all the Contacts.
    QSqlQuery contactsQuery("SELECT * FROM Contact");

    if(!TestQuery(contactsQuery))
        return ContactManager();

    // The ContactManager to feed.
    ContactManager cm;

    while(contactsQuery.next())
    {
        // Creating the Contact from the database.
        Contact c;
            c.setFirstName(contactsQuery.value("FirstName").toString().toStdString());
            c.setLastName(contactsQuery.value("LastName").toString().toStdString());
            c.setCompany(contactsQuery.value("Company").toString().toStdString());
            c.setEmail(contactsQuery.value("Email").toString().toStdString());
            c.setPhone(contactsQuery.value("Phone").toString().toStdString());
            c.setPhotoPath(contactsQuery.value("PhotoPath").toString().toStdString());
            c.setDate(Date::parseDate(contactsQuery.value("CreationDate").toString().toStdString()).value());

        // Getting all the Interactions related to the current Contact.
        QSqlQuery interactionsQuery;
            interactionsQuery.prepare("SELECT * FROM Interaction WHERE Interaction.cID = :cID");
            interactionsQuery.bindValue(":cID", contactsQuery.value("cID").toUInt());

        if(!TestQuery(interactionsQuery))
            return ContactManager();

        // The InteractionManager to feed.
        InteractionManager im;

        while(interactionsQuery.next())
        {
            // Creating the Interaction from the database.
            Interaction i(interactionsQuery.value("Content").toString().toStdString(),
                          Date::parseDate(interactionsQuery.value("CreationDate").toString().toStdString()).value());

            // Getting all the Todos related to the current Interaction.
            QSqlQuery todosQuery;
                todosQuery.prepare("SELECT * FROM Todo WHERE Todo.iID = :iID");
                todosQuery.bindValue(":iID", interactionsQuery.value("iID").toUInt());

            if(!TestQuery(todosQuery))
                return ContactManager();

            // The TodoManager to feed.
            TodoManager tm;

            while(todosQuery.next())
            {
                // Feeding the TodoManager from the database content.
                tm.add({todosQuery.value("Content").toString().toStdString(),
                       Date::parseDate(todosQuery.value("Date").toString().toStdString()).value()});
            }

            i.setTodos(tm);
            im.add(std::move(i));
        }

        c.setInteractionManager(im);
        cm.add(std::move(c));
    }

    db.close();

    return cm;
}

bool DBInterface::SaveData(const ContactManager& contacts)
{
    if(!db.open())
    {
        qDebug() << "Couldn't open " DATABASE_PATH ". Data save failed.";
        return false;
    }

    // Deleting database contents and resetting auto increment IDs.
    {
        if(!TestQuery(QSqlQuery("DELETE FROM Contact")))
            return false;
        if(!TestQuery(QSqlQuery("UPDATE sqlite_sequence SET seq = 0 WHERE name = 'Contact'")))
            return false;

        if(!TestQuery(QSqlQuery("DELETE FROM Interaction")))
            return false;
        if(!TestQuery(QSqlQuery("UPDATE sqlite_sequence SET seq = 0 WHERE name = 'Interaction'")))
            return false;

        if(!TestQuery(QSqlQuery("DELETE FROM Todo")))
            return false;
        if(!TestQuery(QSqlQuery("UPDATE sqlite_sequence SET seq = 0 WHERE name = 'Todo'")))
            return false;
    }

    // Saving content

    for(const auto& c : contacts)
    {
        // Inserting each contact into the database.
        QSqlQuery contactQuery;
            contactQuery.prepare
            (
                "INSERT INTO Contact(FirstName, LastName, Company, Email, Phone, PhotoPath, CreationDate) "
                "VALUES(:FirstName, :LastName, :Company, :Email, :Phone, :PhotoPath, :CreationDate)"
            );

            contactQuery.bindValue(":FirstName", QString::fromStdString(c.getFirstName()));
            contactQuery.bindValue(":LastName", QString::fromStdString(c.getLastName()));
            contactQuery.bindValue(":Company", QString::fromStdString(c.getCompany()));
            contactQuery.bindValue(":Email", QString::fromStdString(c.getEmail()));
            contactQuery.bindValue(":Phone", QString::fromStdString(c.getPhone()));
            contactQuery.bindValue(":PhotoPath", QString::fromStdString(c.getPhotoPath()));
            contactQuery.bindValue(":CreationDate", QString::fromStdString(static_cast<std::string>(c.getDate())));

        if(!TestQuery(contactQuery))
            return false;

        // Getting the ID of the Contact we just inserted.
        int cID;

        if(auto val = GetLastTableID("Contact"); val.has_value()) cID = val.value();
        else return false;

        for(const auto& i : c.getInteractions())
        {
            // Inserting each Interaction into the database.
            QSqlQuery interactionQuery;
                interactionQuery.prepare
                (
                    "INSERT INTO Interaction(cID, Content, CreationDate) "
                    "VALUES(:cID, :Content, :CreationDate)"
                );

                interactionQuery.bindValue(":cID", cID);

                interactionQuery.bindValue(":Content", QString::fromStdString(i.getContent()));
                interactionQuery.bindValue(":CreationDate", QString::fromStdString(static_cast<std::string>(i.getDate())));

            if(!TestQuery(interactionQuery))
                return false;

            // Getting the ID of the Interaction we just inserted.
            int iID;

            if(auto val = GetLastTableID("Interaction"); val.has_value()) iID = val.value();
            else return false;

            for(const auto& t : i.getTodos())
            {
                // Inserting each Todo into the database.
                QSqlQuery todoQuery;
                    todoQuery.prepare
                    (
                        "INSERT INTO Todo(iID, Content, Date) "
                        "VALUES(:iID, :Content, :Date)"
                    );

                    todoQuery.bindValue(":iID", iID);
                    todoQuery.bindValue(":Content", QString::fromStdString(t.getContent()));
                    todoQuery.bindValue(":Date", QString::fromStdString(static_cast<std::string>(t.getDate())));

                if(!TestQuery(todoQuery))
                    return false;
            }
        }
    }

    db.close();

    // Saved successfully.
    return true;
}

bool DBInterface::TestQuery(QSqlQuery& q)
{
    if(!q.exec())
    {
        qDebug() << "SQL request " << q.lastQuery() << " failed.";
        qDebug() << q.lastError();
        return false;
    }

    return true;
}

// For on-the-fly created QSqlQueries.
bool DBInterface::TestQuery(QSqlQuery&& q)
{
    return TestQuery(q);
}

std::optional<int> DBInterface::GetLastTableID(const std::string& tableName)
{
    // Sqlite stores auto increment IDs in "sqlite_sequence" table.
    QSqlQuery q;
        q.prepare("SELECT seq FROM sqlite_sequence WHERE name = :tableName");
        q.bindValue(":tableName", QString::fromStdString(tableName));

    if(!TestQuery(q))
        return std::optional<int>();

    q.next();

    return q.value("seq").toInt();
}
