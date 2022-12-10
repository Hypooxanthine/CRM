#pragma once

#include <QWidget>

#include "DataStructures/contact.h"

class QHBoxLayout;
class QLabel;
class QPushButton;

class ContactEntry : public QWidget
{
    Q_OBJECT
public:
    explicit ContactEntry(QWidget *parent, const Contact& c);

    void setContact(const Contact& c);

signals:
    void deleted(const Contact& c);

private:
    Contact contact;
    QHBoxLayout* layout;

    QLabel* lPhoto;
    QLabel* lName;
    QPushButton* bEdit;
    QPushButton* bDelete;

private slots:
    void emitDeleted();
    void openEditContact(const Contact& c);
};
