#include "HUD/contactexplorer.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QFrame>
#include <QLabel>

#include "DataStructures/contact.h"
#include "DataStructures/contactmanager.h"

ContactExplorer::ContactExplorer(QWidget *parent, const ContactManager* contacts)
    : QWidget(parent), contacts(contacts), mainLayout(new QVBoxLayout()),
      contactsLayout(new QGridLayout()), contactsArea(new QScrollArea(this))
{
    // Main layout
    mainLayout->addWidget(contactsArea);

    // Scroll area
    contactsArea->setLayout(contactsLayout);
    contactsArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    contactsArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // Contacts layout
    contactsLayout->setAlignment(Qt::AlignTop);
    contactsLayout->setMargin(0);
    contactsLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(mainLayout);

    refreshContacts();
}

void ContactExplorer::refreshContacts()
{
    clearContacts();
    addHeader();

    // 1 because there is already the header in first row.
    size_t i = 1;

    for(const auto& c : *contacts)
    {
        uint8_t j = 0;
        contactsLayout->addWidget(new QLabel(c.getFirstName().c_str(), contactsArea), i, j++);
        contactsLayout->addWidget(new QLabel(c.getLastName().c_str(), contactsArea), i, j++);
        contactsLayout->addWidget(new QLabel(c.getPhone().c_str(), contactsArea), i, j++);
        contactsLayout->addWidget(new QLabel(c.getEmail().c_str(), contactsArea), i, j++);
        contactsLayout->addWidget(new QLabel(static_cast<std::string>(c.getDate()).c_str()), i, j++);

        QPushButton* bShowInteractions = new QPushButton(tr("Show interactions"), contactsArea);
        QPushButton* bAddInteraction = new QPushButton(tr("Add interaction"), contactsArea);
        QPushButton* bEdit = new QPushButton(tr("Edit"), contactsArea);
        QPushButton* bDelete = new QPushButton(tr("Delete"), contactsArea);

        contactsLayout->addWidget(bShowInteractions, i, j++);
        contactsLayout->addWidget(bAddInteraction, i, j++);
        contactsLayout->addWidget(bEdit, i, j++);
        contactsLayout->addWidget(bDelete, i, j++);

        QWidget::connect(bDelete, &QPushButton::clicked, this, [this, &c](){ emit deletedContact(c); });

        i++;
    }
}

void ContactExplorer::clearContacts()
{
    QLayoutItem* child;

    while((child = contactsLayout->takeAt(0)) != nullptr)
        delete child->widget();
}

void ContactExplorer::addHeader()
{
    uint8_t i = 0;

    QPushButton* bFirstName = new QPushButton(tr("First name"), contactsArea);
    QPushButton* bLastName = new QPushButton(tr("Last name"), contactsArea);
    QPushButton* bPhone = new QPushButton(tr("Phone number"), contactsArea);
    QPushButton* bEmail = new QPushButton(tr("Email"), contactsArea);
    QPushButton* bCreationDate = new QPushButton(tr("Creation date"), contactsArea);

    contactsLayout->addWidget(bFirstName, 0, i++);
    contactsLayout->addWidget(bLastName, 0, i++);
    contactsLayout->addWidget(bPhone, 0, i++);
    contactsLayout->addWidget(bEmail, 0, i++);
    contactsLayout->addWidget(bCreationDate, 0, i++);

    QWidget::connect(bFirstName, &QPushButton::clicked, this, [this](){ emit askedSort(SortType::FirstName); });
    QWidget::connect(bLastName, &QPushButton::clicked, this, [this](){ emit askedSort(SortType::LastName); });
    QWidget::connect(bPhone, &QPushButton::clicked, this, [this](){ emit askedSort(SortType::Phone); });
    QWidget::connect(bEmail, &QPushButton::clicked, this, [this](){ emit askedSort(SortType::Email); });
    QWidget::connect(bCreationDate, &QPushButton::clicked, this, [this](){ emit askedSort(SortType::CreationDate); });
}
