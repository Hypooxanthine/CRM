#include "HUD/Todos/todotab.h"

#include <QVBoxLayout>

#include "DataStructures/contactmanager.h"

#include "HUD/Todos/todoexplorer.h"

TodoTab::TodoTab(ContactManager* contacts, QWidget *parent)
    : QWidget(parent), contacts(contacts), mainLayout(new QVBoxLayout()), explorer(new TodoExplorer(contacts))
{
    setLayout(mainLayout);
    mainLayout->addWidget(explorer);
}

void TodoTab::updateContacts()
{
    explorer->refresh();
}
