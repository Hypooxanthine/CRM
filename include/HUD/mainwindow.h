#pragma once

#include <QMainWindow>
#include <QTabWidget>

#include "DataStructures/contactmanager.h"

class ContactExplorer;
class TodoExplorer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    ContactManager contacts;

    QTabWidget* tabs;
    ContactExplorer* contactsTab;
    TodoExplorer* todosTab;
};
