#include "HUD/contacttab.h"

#include <QHBoxLayout>

#include "HUD/contacttoolbar.h"
#include "HUD/contactexplorer.h"

#include "DataStructures/contactmanager.h"

ContactTab::ContactTab(QWidget* parent, ContactManager* contacts)
    : QWidget(parent), contacts(contacts), mainLayout(new QHBoxLayout()),
      toolbar(new ContactToolbar(this)), explorer(new ContactExplorer(this, contacts))
{
    // Main layout
    mainLayout->addWidget(toolbar);
    mainLayout->addWidget(explorer);

    setLayout(mainLayout);
}
