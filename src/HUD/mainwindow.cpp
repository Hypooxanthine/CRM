#include "HUD/mainwindow.h"

#include <QPushButton>
#include <QToolButton>
#include <QFileDialog>

#include "DataStructures/contactmanager.h"
#include "ExtData/dbinterface.h"
#include "ExtData/JsonInterface.h"
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

    toolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, toolBar);

    QAction* exportAction =new QAction("&Export jsonDATA", this);
    toolBar->addAction(exportAction);
    QObject::connect(exportAction, SIGNAL(triggered()), this, SLOT(exportJsonAction()));

    QAction* importAction =new QAction("&Import jsonDATA", this);
    toolBar->addAction(importAction);
    QObject::connect(importAction, SIGNAL(triggered()), this, SLOT(importJsonAction()));

}

MainWindow::~MainWindow()
{
    DBInterface::SaveData(contacts);
}

void MainWindow::exportJsonAction()
{
    auto path = QFileDialog::getOpenFileName(this, tr("choose a json file"), QDir::currentPath());
    JsonInterface::ExportData(this->contacts,path);
}

void MainWindow::importJsonAction()
{
    auto path = QFileDialog::getOpenFileName(this, tr("choose a json file"), QDir::currentPath());
    this->contacts = JsonInterface::ImportData(path);
    this->contactsTab = new ContactTab(tabs, &contacts);
    this->todosTab = new TodoExplorer(tabs);
}
