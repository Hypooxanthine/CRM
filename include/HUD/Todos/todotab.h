#pragma once

#include <QWidget>

class ContactManager;

class TodoTab : public QWidget
{
    Q_OBJECT
public:
    explicit TodoTab(ContactManager* contacts, QWidget *parent = nullptr);

signals:

};

