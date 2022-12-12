#pragma once

#include <QWidget>

class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QSpinBox;
class QDateEdit;
class QPushButton;

class ContactSearch : public QWidget
{
    Q_OBJECT
public:
    explicit ContactSearch(QWidget *parent = nullptr);

    QString getFirstName() const;
    QString getLastName() const;
    QString getCompany() const;
    int getContactsNumber() const;
    QDate getFromDate() const;
    QDate getToDate() const;

signals:
    void searched();

private: // Private members
    // Layouts
    QHBoxLayout* mainLayout;
    QHBoxLayout* numberLayout;
    QHBoxLayout* creationLayout;
    QVBoxLayout* creationDatesLayout;
    QHBoxLayout* fromDateLayout;
    QHBoxLayout* toDateLayout;
    QVBoxLayout* nameLayout;
    QHBoxLayout* firstNameLayout;
    QHBoxLayout* lastNameLayout;
    QHBoxLayout* companyLayout;

    // Labels
    QLabel* numberLabel;
    QLabel* creationLabel;
    QLabel* fromDateLabel;
    QLabel* toDateLabel;
    QLabel* firstNameLabel;
    QLabel* lastNameLabel;
    QLabel* companyLabel;

    // Line edits
    QLineEdit* firstNameEdit;
    QLineEdit* lastNameEdit;
    QLineEdit* companyEdit;

    // Spin boxes
    QSpinBox* numberSpin;

    // Date edits
    QDateEdit* fromDateEdit;
    QDateEdit* toDateEdit;

    // Buttons
    QPushButton* searchButton;

};
