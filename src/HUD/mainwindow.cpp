#include "HUD/mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QToolButton>
#include <QFileDialog>
#include <QApplication>

#include "DataStructures/contactmanager.h"
#include "ExtData/dbinterface.h"
#include "ExtData/JsonInterface.h"
#include "HUD/Contacts/contacttab.h"
#include "HUD/Todos/todotab.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), contacts(DBInterface::LoadData()),
      tabs(new QTabWidget(this)),
      contactsTab(new ContactTab(tabs, &contacts)),
      todosTab(new TodoTab(&contacts, tabs))
{
    // The window is maximized : it fills the screen but is not in fullscreen.
    showMaximized();
    setWindowTitle(tr("Contacts Manager"));

    setCentralWidget(tabs);
    tabs->addTab(contactsTab, tr("Contacts"));
    tabs->addTab(todosTab, tr("Upcoming tasks"));

    toolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, toolBar);

    QAction* exportAction = new QAction(tr("&Export to json"), this);
    toolBar->addAction(exportAction);
    QObject::connect(exportAction, SIGNAL(triggered()), this, SLOT(exportJsonAction()));

    QAction* importAction = new QAction(tr("&Import from json"), this);
    toolBar->addAction(importAction);
    QObject::connect(importAction, SIGNAL(triggered()), this, SLOT(importJsonAction()));

    QWidget::connect(contactsTab, SIGNAL(updated()), todosTab, SLOT(updateContacts()));

}

MainWindow::~MainWindow()
{
    DBInterface::SaveData(contacts);
}

void MainWindow::exportJsonAction()
{
    auto path = QFileDialog::getSaveFileName(this, tr("Export to json"), QDir::currentPath());
    if(path.isEmpty()) return;

    JsonInterface::ExportData(this->contacts, path);
}

void MainWindow::importJsonAction()
{
    auto path = QFileDialog::getOpenFileName(this, tr("Import from json"), QDir::currentPath());
    if(path.isEmpty()) return;

    this->contacts = JsonInterface::ImportData(path);
    this->contactsTab = new ContactTab(tabs, &contacts);
    this->todosTab = new TodoTab(&contacts, tabs);
}
