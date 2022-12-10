#pragma once

#include <vector>

#include <QWidget>

class ContactEntry;
class QVBoxLayout;

class ContactExplorer : public QWidget
{
    Q_OBJECT

public:
    ContactExplorer(QWidget* parent);

private:
    QVBoxLayout* entriesLayout;
    std::vector<ContactEntry*> entries;
};
