#pragma once

#include <vector>

#include <QWidget>

class QVBoxLayout;

class ContactManager;
class Contact;
class ContactEntry;

class ContactExplorer : public QWidget
{
    Q_OBJECT

public:
    ContactExplorer(QWidget* parent, ContactManager* contacts);

private:
    void addContact(const Contact& c);

private:
    ContactManager* contacts;

    QVBoxLayout* entriesLayout;
    std::vector<ContactEntry*> entries;
};
