#include "HUD/mainwindow.h"

#include <QPushButton>

#include "DataStructures/contactmanager.h"
#include "ExtData/dbinterface.h"
#include "HUD/Contacts/contacttab.h"
#include "HUD/Todos/todoexplorer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), contacts(DBInterface::LoadData()),
      tabs(new QTabWidget(this)),
      contactsTab(new ContactTab(tabs, &contacts)),
      todosTab(new TodoExplorer(tabs))
{
    // The window is maximized : it fills the screen but is not in fullscreen.
    showMaximized();
    setWindowTitle(tr("Contacts Manager"));

    setCentralWidget(tabs);
    tabs->addTab(contactsTab, tr("Contacts"));
    tabs->addTab(todosTab, tr("Upcoming tasks"));
}

MainWindow::~MainWindow()
{
    DBInterface::SaveData(contacts);
}

