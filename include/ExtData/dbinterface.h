#pragma once

#include "DataStructures/contactmanager.h"

#include <QtSql/QSqlDatabase>

class DBInterface
{
public: // Public methods
    static void Init();
    static ContactManager GetData();
    static void SaveData(const ContactManager& contacts);

private: // Private methods


private: // Private members
    static QSqlDatabase db;
};
