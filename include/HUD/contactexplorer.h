#pragma once

#include <QWidget>

#include "DataStructures/contact.h"
#include "DataStructures/contactmanager.h"

class QHBoxLayout;
class QGridLayout;
class QScrollArea;

class ContactEdit;

class ContactExplorer : public QWidget
{
    Q_OBJECT
public: // Public methods
    explicit ContactExplorer(QWidget *parent, ContactManager* contacts);

    void setRestrictedContacts(const ContactManager& contacts);
    void setRestrictedContacts(ContactManager&& contacts);

signals:
    void requestExtraction();

public slots:
    void refreshContacts();

private slots:
    void requestEditContactWindow(Contact& contact);
    void editContact(const Contact& newContact);
    void deleteContact(const Contact& contact);
    void sortContacts(const ContactManager::SortValue& sort);

private: // Private methods
    void clearContacts();
    void addHeader();

private: // Private members
    ContactManager* contacts;
    ContactManager restrictedContacts;

    ContactEdit* contactEdit = nullptr;

    QHBoxLayout* mainLayout;
    QGridLayout* explorerLayout;
    QScrollArea* contactsArea;

    Contact modifyingContact;

    ContactManager::SortValue currentSortValue = ContactManager::SortValue::FirstName;
    ContactManager::SortType currentSortType = ContactManager::SortType::Ascending;
};
