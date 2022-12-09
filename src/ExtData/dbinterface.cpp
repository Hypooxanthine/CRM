#include "ExtData/dbinterface.h"

#include <qdebug.h>
#include <QtSql/QSqlQuery>

#define DATABASE_PATH "/Data/data.db"

QSqlDatabase DBInterface::db = QSqlDatabase::addDatabase("QSQLITE");

void DBInterface::Init()
{
    db.setDatabaseName(DATABASE_PATH);
}

ContactManager DBInterface::GetData()
{
    // Couldn't open database : we return an empty ContactManager.
    if(!db.open())
    {
        qDebug() << "Couldn't open " DATABASE_PATH ".";
        return ContactManager();
    }

    QSqlQuery contactsQuery("SELECT * FROM Contact");
    contactsQuery.exec();

    ContactManager cm;

    while(contactsQuery.next())
    {
        Contact c;
            c.setFirstName(contactsQuery.value("FirstName").toString().toStdString());
            c.setLastName(contactsQuery.value("LastName").toString().toStdString());
            c.setEmail(contactsQuery.value("Email").toString().toStdString());
            c.setPhone(contactsQuery.value("Phone").toString().toStdString());
            c.setPhotoPath(contactsQuery.value("PhotoPath").toString().toStdString());
            c.setDate(Date::parseDate(contactsQuery.value("CreationDate").toString().toStdString()).value());

        QSqlQuery interactionsQuery("SELECT * FROM Interaction WHERE Interaction.cID = :cID");
            interactionsQuery.bindValue(":cID", contactsQuery.value("cID").toUInt());

        interactionsQuery.exec();

        InteractionManager im;

        while(interactionsQuery.next())
        {
            Interaction i(interactionsQuery.value("Content").toString().toStdString(),
                          Date::parseDate(interactionsQuery.value("CreationDate").toString().toStdString()).value());

            QSqlQuery todosQuery("SELECT * FROM Todo WHERE Todo.iID = :iID");
                todosQuery.bindValue(":iID", interactionsQuery.value("iID").toUInt());

            todosQuery.exec();

            TodoManager tm;

            while(todosQuery.next())
            {
                tm.add({todosQuery.value("Content").toString().toStdString(),
                       Date::parseDate(todosQuery.value("Date").toString().toStdString()).value()});
            }

            im.add(std::move(i));
        }

        cm.add(std::move(c));
    }

    db.close();

    return cm;
}

void DBInterface::SaveData(const ContactManager& contacts)
{
    if(!db.open())
    {
        qDebug() << "Couldn't open " DATABASE_PATH ". Data save failed.";
        return;
    }

    // Deleting database contents
    QSqlQuery("DELETE FROM Contact").exec();
    QSqlQuery("DELETE FROM Interaction").exec();
    QSqlQuery("DELETE FROM Todo").exec();

    // Saving content

    for(const auto& c : contacts)
    {
        QSqlQuery contactQuery
        (
            "INSERT INTO Contact(FirstName, LastName, Email, Phone, PhotoPath, CreationDate) "
            "VALUES(:1, :2, :3, :4, :5, :6)"
        );

        contactQuery.bindValue(":1", QString::fromStdString(c.getFirstName()));
        contactQuery.bindValue(":2", QString::fromStdString(c.getLastName()));
        contactQuery.bindValue(":3", QString::fromStdString(c.getEmail()));
        contactQuery.bindValue(":4", QString::fromStdString(c.getPhone()));
        contactQuery.bindValue(":5", QString::fromStdString(c.getPhotoPath()));
        contactQuery.bindValue(":6", QString::fromStdString(static_cast<std::string>(c.getDate())));

        contactQuery.exec();

        for(const auto& i : c.getInteractions())
        {
            QSqlQuery interactionQuery
            (
                "INSERT INTO Interaction(cID, Content, CreationDate) "
                "VALUES(:1, :2, :3)"
            );

            interactionQuery.bindValue(":1", contactQuery.lastInsertId());
            interactionQuery.bindValue(":2", QString::fromStdString(i.getContent()));
            interactionQuery.bindValue(":3", QString::fromStdString(static_cast<std::string>(i.getDate())));

            interactionQuery.exec();

            for(const auto& t : i.getTodos())
            {
                QSqlQuery todoQuery
                (
                    "INSERT INTO Todo(iID, Content, Date) "
                    "VALUES(:1, :2, :3)"
                );

                todoQuery.bindValue(":1", interactionQuery.lastInsertId());
                todoQuery.bindValue(":2", QString::fromStdString(t.getContent()));
                todoQuery.bindValue(":3", QString::fromStdString(static_cast<std::string>(t.getDate())));

                todoQuery.exec();
            }
        }
    }

    db.close();
}
