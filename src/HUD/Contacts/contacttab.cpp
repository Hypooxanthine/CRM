#include "HUD/Contacts/contacttab.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QDate>

#include "HUD/Contacts/contactsearch.h"
#include "HUD/Contacts/contactexplorer.h"
#include "HUD/Contacts/contactedit.h"

#include "DataStructures/contactmanager.h"
#include "DataStructures/contact.h"

ContactTab::ContactTab(QWidget* parent, ContactManager* contacts)
    : QWidget(parent), contacts(contacts), mainLayout(new QVBoxLayout()),
      bNewContact(new QPushButton(tr("Add new contact"), this)),
      searcher(new ContactSearch(this)),
      explorer(new ContactExplorer(this, contacts))
{
    // Main layout
    mainLayout->addWidget(bNewContact);
    mainLayout->addWidget(searcher);
    mainLayout->addWidget(explorer);

    setLayout(mainLayout);

    QWidget::connect(bNewContact, SIGNAL(clicked()), this, SLOT(requestNewContactWindow()));
    QWidget::connect(searcher, SIGNAL(searched()), this, SLOT(extractContacts()));
    QWidget::connect(explorer, SIGNAL(requestExtraction()), this, SLOT(extractContacts()));
    QWidget::connect(explorer, SIGNAL(deletedContact(const Contact&)), this, SLOT(deleteContact(const Contact&)));
    QWidget::connect(explorer, SIGNAL(editedContact(const Contact&, const Contact&)), this, SLOT(editContact(const Contact&, const Contact&)));

    extractContacts();
}

void ContactTab::requestNewContactWindow()
{
    ContactEdit* nc = new ContactEdit(tr("Contact creation"));

    QWidget::connect(nc, SIGNAL(validate(Contact)), this, SLOT(addContact(const Contact&)));

    nc->show();
}

void ContactTab::addContact(const Contact& contact)
{
    // We do not add a contact that already exists in the contacts manager.
    if(contacts->find(contact) != contacts->end())
    {
        QMessageBox::warning(nullptr, tr("Warning"), tr("This contact already exists and therefore won't be added to the contacts list."));
        return;
    }

    contacts->add(contact);
    extractContacts();
}

void ContactTab::extractContacts()
{
    ContactManager extracted = *contacts;

    if(!searcher->getFirstName().isEmpty())
        extracted = extracted.extractByFirstName(searcher->getFirstName().toStdString());
    if(!searcher->getLastName().isEmpty())
        extracted = extracted.extractByLastName(searcher->getLastName().toStdString());
    if(!searcher->getCompany().isEmpty())
        extracted = extracted.extractByCompany(searcher->getCompany().toStdString());

    // Creation date
    {
        Date from, to;
        QDate qFrom = searcher->getFromDate();
        QDate qTo = searcher->getToDate();

        from.setYear(qFrom.year());
        from.setMonth(qFrom.month());
        from.setDay(qFrom.day());
        to.setYear(qTo.year());
        to.setMonth(qTo.month());
        to.setDay(qTo.day());

        extracted = extracted.extractByCreationDate(from, to);
    }

    // Last edit date
    {
        Date from, to;
        QDate qFrom = searcher->getFromLastEditDate();
        QDate qTo = searcher->getToLastEditDate();

        from.setYear(qFrom.year());
        from.setMonth(qFrom.month());
        from.setDay(qFrom.day());
        to.setYear(qTo.year());
        to.setMonth(qTo.month());
        to.setDay(qTo.day());

        extracted = extracted.extractByLastEditDate(from, to);
    }

    extracted = extracted.extractHeadNumber(searcher->getContactsNumber());

    explorer->setRestrictedContacts(std::move(extracted));

    emit updated();
}

void ContactTab::deleteContact(const Contact& contact)
{
    contacts->remove(contact);

    extractContacts();
}

void ContactTab::editContact(const Contact& oldContact, const Contact& newContact)
{
    auto oldIt = contacts->find(oldContact);
    if(oldIt != contacts->end())
    {
        *oldIt = newContact;
        oldIt->setLastEditDate(Date::today());
        extractContacts();
    }
}
