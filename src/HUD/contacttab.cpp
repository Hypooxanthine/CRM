#include "HUD/contacttab.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

#include "HUD/contactexplorer.h"
#include "HUD/contactedit.h"

#include "DataStructures/contactmanager.h"
#include "DataStructures/contact.h"

ContactTab::ContactTab(QWidget* parent, ContactManager* contacts)
    : QWidget(parent), contacts(contacts), mainLayout(new QVBoxLayout()),
      bNewContact(new QPushButton(tr("Add new contact"), this)),
      explorer(new ContactExplorer(this, contacts))
{
    // Main layout
    mainLayout->addWidget(bNewContact);
    mainLayout->addWidget(explorer);

    setLayout(mainLayout);

    QWidget::connect(bNewContact, SIGNAL(clicked()), this, SLOT(requestNewContactWindow()));
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
    explorer->refreshContacts();
}
