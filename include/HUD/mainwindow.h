#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>

class ContactExplorer;
class TodoExplorer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTabWidget* tabs;
    ContactExplorer* contactsTab;
    TodoExplorer* todosTab;
};
#endif // MAINWINDOW_H
