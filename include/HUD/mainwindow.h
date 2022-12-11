#pragma once

#include <QMainWindow>
#include <QTabWidget>

#include "DataStructures/contactmanager.h"

class ContactTab;
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
    ContactTab* contactsTab;
    TodoExplorer* todosTab;
};
