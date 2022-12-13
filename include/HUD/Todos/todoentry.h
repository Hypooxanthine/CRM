#pragma once

#include <QWidget>

class QHBoxLayout;
class QLabel;
class QPushButton;

class Contact;
class Interaction;
class Todo;

class TodoEntry : public QWidget
{
    Q_OBJECT
public:
    explicit TodoEntry(Todo* todo, Interaction* interaction, Contact* contact, QWidget *parent = nullptr);

    inline Contact* getContact() { return contact; }
    inline Interaction* getInteraction() { return interaction; }
    inline Todo* getTodo() { return todo; }

signals:
    void deleted(Contact*, Interaction*, Todo*);

private:
    Todo* todo;
    Interaction* interaction;
    Contact* contact;

    // Layouts
    QHBoxLayout* mainLayout;

    // Widgets
    QLabel* text;
    QLabel* date;
    QPushButton* deleteButton;

};
