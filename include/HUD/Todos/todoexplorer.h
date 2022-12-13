#pragma once

#include <tuple>

#include <QWidget>

class QVBoxLayout;
class QScrollArea;

class ContactManager;
class Todo;
class Contact;
class Interaction;

class TodoExplorer : public QWidget
{
    Q_OBJECT
public:
    explicit TodoExplorer(ContactManager* contacts, QWidget *parent = nullptr);

public slots:
    void refresh();

signals:

private slots:
    void removeTodo(Contact*, Interaction*, Todo*);

private: // Private methods
    void addTodoEntry(Contact* contact, Interaction* interaction, Todo* todo);

private: // Private members
    ContactManager* contacts;

    // Layouts
    QVBoxLayout* mainLayout;
    QVBoxLayout* explorerLayout;
    QScrollArea* todosArea;
};
