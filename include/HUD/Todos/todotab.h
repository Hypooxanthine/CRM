#pragma once

#include <QWidget>

class QVBoxLayout;

class ContactManager;
class TodoExplorer;

class TodoTab : public QWidget
{
    Q_OBJECT
public:
    explicit TodoTab(ContactManager* contacts, QWidget *parent = nullptr);

signals:

public slots:
    void updateContacts();

private: // Private members
    ContactManager* contacts;

    QVBoxLayout* mainLayout;

    TodoExplorer* explorer;

};

