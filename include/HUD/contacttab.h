#pragma once

#include <vector>

#include <QWidget>

class QHBoxLayout;
class QTableWidget;

class ContactManager;
class Contact;

class ContactToolbar;
class ContactExplorer;

class ContactTab : public QWidget
{
    Q_OBJECT

public: // Public methods
    ContactTab(QWidget* parent, ContactManager* contacts);

private: // Private methods

private: // Private members
    ContactManager* contacts;

    QHBoxLayout* mainLayout;
    ContactToolbar* toolbar;
    ContactExplorer* explorer;
};
