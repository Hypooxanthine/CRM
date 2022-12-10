#include "HUD/mainwindow.h"

#include <QPushButton>

#include "HUD/contactexplorer.h"
#include "HUD/todoexplorer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), tabs(new QTabWidget(this)), contactsTab(new ContactExplorer(tabs)), todosTab(new TodoExplorer(tabs))
{
    // The window is maximized : it fills the screen but is not in fullscreen.
    showMaximized();

    setCentralWidget(tabs);
    tabs->addTab(contactsTab, tr("Contacts"));
    tabs->addTab(todosTab, tr("Upcoming tasks"));
}

MainWindow::~MainWindow()
{
}

