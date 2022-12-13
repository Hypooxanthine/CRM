#pragma once

#include <QMainWindow>
#include <QTabWidget>
#include <QToolBar>

#include "DataStructures/contactmanager.h"

class ContactTab;
class TodoTab;

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
    TodoTab* todosTab;

    QToolBar* toolBar;



private slots:
    void exportJsonAction();

    void importJsonAction();
};
