#pragma once

#include <vector>

#include <QWidget>

class QVBoxLayout;
class QTableWidget;
class QPushButton;

class ContactManager;
class Contact;

class ContactSearch;
class ContactExplorer;

class ContactTab : public QWidget
{
    Q_OBJECT

public: // Public methods
    ContactTab(QWidget* parent, ContactManager* contacts);

private: // Private methods

private slots:
    void requestNewContactWindow();
    void addContact(const Contact& c);
    void extractContacts();

private: // Private members
    ContactManager* contacts;

    QVBoxLayout* mainLayout;

    QPushButton* bNewContact;
    ContactSearch* searcher;
    ContactExplorer* explorer;
};
