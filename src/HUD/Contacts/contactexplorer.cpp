#include "HUD/Contacts/contactexplorer.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QFrame>
#include <QLabel>
#include <QMessageBox>

#include "HUD/Contacts/contactedit.h"

ContactExplorer::ContactExplorer(QWidget *parent, ContactManager* contacts)
    : QWidget(parent), contacts(contacts), mainLayout(new QHBoxLayout()),
      explorerLayout(new QGridLayout()), contactsArea(new QScrollArea(this))
{
    // Main layout
    mainLayout->addWidget(contactsArea);

    // Explorer layout
    explorerLayout->setAlignment(Qt::AlignTop);
    //explorerLayout->setMargin(0);
    explorerLayout->setContentsMargins(0, 0, 0, 0);
    explorerLayout->setSizeConstraint(QLayout::SetMinimumSize);

    // Scroll area
    QWidget* scrollWidget = new QWidget();
    scrollWidget->setLayout(explorerLayout);
    contactsArea->setWidget(scrollWidget);
    contactsArea->setWidgetResizable(true);

    setLayout(mainLayout);

    refreshContacts();
}

void ContactExplorer::setRestrictedContacts(const ContactManager& contacts)
{
    restrictedContacts = contacts;

    restrictedContacts.sort(currentSortValue, currentSortType);
    refreshContacts();
}

void ContactExplorer::setRestrictedContacts(ContactManager&& contacts)
{
    restrictedContacts = contacts;

    restrictedContacts.sort(currentSortValue, currentSortType);
    refreshContacts();
}

void ContactExplorer::refreshContacts()
{
    clearContacts();
    addHeader();

    // 1 because there is already the header in first row.
    size_t i = 1;

    for(auto& c : restrictedContacts)
    {
        uint8_t j = 0;
        explorerLayout->addWidget(new QLabel(c.getFirstName().c_str(), contactsArea), i, j++);
        explorerLayout->addWidget(new QLabel(c.getLastName().c_str(), contactsArea), i, j++);
        explorerLayout->addWidget(new QLabel(c.getCompany().c_str(), contactsArea), i, j++);
        explorerLayout->addWidget(new QLabel(c.getPhone().c_str(), contactsArea), i, j++);
        explorerLayout->addWidget(new QLabel(c.getEmail().c_str(), contactsArea), i, j++);
        explorerLayout->addWidget(new QLabel(static_cast<std::string>(c.getDate()).c_str()), i, j++);
        explorerLayout->addWidget(new QLabel(static_cast<std::string>(c.getLastEditDate()).c_str()), i, j++);

        QPushButton* bMore = new QPushButton(tr("..."), contactsArea);
        QPushButton* bDelete = new QPushButton(tr("Delete"), contactsArea);

        explorerLayout->addWidget(bMore, i, j++);
        explorerLayout->addWidget(bDelete, i, j++);

        QWidget::connect(bDelete, &QPushButton::clicked, this, [this, &c](){ deleteContact(c); });
        QWidget::connect(bMore, &QPushButton::clicked, this, [this, &c](){ requestEditContactWindow(c); });

        i++;
    }
}

void ContactExplorer::clearContacts()
{
    QLayoutItem* child;

    while((child = explorerLayout->takeAt(0)) != nullptr)
        delete child->widget();
}

void ContactExplorer::addHeader()
{
    uint8_t i = 0;

    QPushButton* bFirstName = new QPushButton(tr("First name"), contactsArea);
    QPushButton* bLastName = new QPushButton(tr("Last name"), contactsArea);
    QPushButton* bCompany = new QPushButton(tr("Company"), contactsArea);
    QPushButton* bPhone = new QPushButton(tr("Phone number"), contactsArea);
    QPushButton* bEmail = new QPushButton(tr("Email"), contactsArea);
    QPushButton* bCreationDate = new QPushButton(tr("Creation date"), contactsArea);
    QPushButton* bLastEditDate = new QPushButton(tr("Last edit date"), contactsArea);

    explorerLayout->addWidget(bFirstName, 0, i++);
    explorerLayout->addWidget(bLastName, 0, i++);
    explorerLayout->addWidget(bCompany, 0, i++);
    explorerLayout->addWidget(bPhone, 0, i++);
    explorerLayout->addWidget(bEmail, 0, i++);
    explorerLayout->addWidget(bCreationDate, 0, i++);
    explorerLayout->addWidget(bLastEditDate, 0, i++);

    QWidget::connect(bFirstName, &QPushButton::clicked, this, [this](){ sortContacts(ContactManager::SortValue::FirstName); });
    QWidget::connect(bLastName, &QPushButton::clicked, this, [this](){ sortContacts(ContactManager::SortValue::LastName); });
    QWidget::connect(bCompany, &QPushButton::clicked, this, [this](){ sortContacts(ContactManager::SortValue::Company); });
    QWidget::connect(bPhone, &QPushButton::clicked, this, [this](){ sortContacts(ContactManager::SortValue::Phone); });
    QWidget::connect(bEmail, &QPushButton::clicked, this, [this](){ sortContacts(ContactManager::SortValue::Email); });
    QWidget::connect(bCreationDate, &QPushButton::clicked, this, [this](){ sortContacts(ContactManager::SortValue::CreationDate); });
    QWidget::connect(bLastEditDate, &QPushButton::clicked, this, [this](){ sortContacts(ContactManager::SortValue::LastEditDate); });
}

void ContactExplorer::requestEditContactWindow(Contact& contact)
{
    modifyingContact = contact;

    if(contactEdit != nullptr) delete contactEdit;

    contactEdit = new ContactEdit(contact);
    mainLayout->addWidget(contactEdit);

    QWidget::connect(contactEdit, SIGNAL(validate(Contact)), this, SLOT(editContact(const Contact&)));
}

void ContactExplorer::editContact(const Contact& newContact)
{
    emit editedContact(modifyingContact, newContact);
}

void ContactExplorer::deleteContact(const Contact& contact)
{
    emit deletedContact(contact);
}

void ContactExplorer::sortContacts(const ContactManager::SortValue& sort)
{
    if(sort == currentSortValue)
    {
        currentSortType = ((currentSortType == ContactManager::SortType::Ascending) ?
                               ContactManager::SortType::Descending :
                               ContactManager::SortType::Ascending);
    }
    else
    {
        currentSortValue = sort;
        currentSortType = ContactManager::SortType::Ascending;
    }

    restrictedContacts.sort(currentSortValue, currentSortType);

    refreshContacts();
}
