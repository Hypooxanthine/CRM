#include "HUD/contactexplorer.h"

#include <QVBoxLayout>

#include "DataStructures/contactmanager.h"
#include "HUD/contactentry.h"

ContactExplorer::ContactExplorer(QWidget* parent, ContactManager* contacts)
    : QWidget(parent), contacts(contacts), entriesLayout(new QVBoxLayout(this))
{
    entriesLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    for(const auto& c : *this->contacts)
    {
        addContact(c);
    }
}

void ContactExplorer::addContact(const Contact& c)
{
    entriesLayout->addWidget(new ContactEntry(this, c));
}
