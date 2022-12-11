#pragma once

#include <QWidget>

class QVBoxLayout;
class QGridLayout;
class QScrollArea;

class Contact;
class ContactManager;

enum class SortType
{
    FirstName = 0, LastName, Phone, Email, CreationDate
};

class ContactExplorer : public QWidget
{
    Q_OBJECT
public: // Public methods
    explicit ContactExplorer(QWidget *parent, const ContactManager* contacts);

public slots:
    void refreshContacts();

signals:
    void askedSort(const SortType& sortType);
    void deletedContact(const Contact& contact);
    void modifiedContact(const Contact& oldContact, const Contact& newContact);

private: // Private methods
    void clearContacts();
    void addHeader();

private: // Private members
    const ContactManager* contacts;

    QVBoxLayout* mainLayout;
    QGridLayout* contactsLayout;
    QScrollArea* contactsArea;
};
