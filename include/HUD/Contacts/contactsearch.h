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
    QDate getFromLastEditDate() const;
    QDate getToLastEditDate() const;

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
    QHBoxLayout* lastEditLayout;
    QVBoxLayout* lastEditDatesLayout;
    QHBoxLayout* fromLastEditDateLayout;
    QHBoxLayout* toLastEditDateLayout;
    QVBoxLayout* nameLayout;
    QHBoxLayout* firstNameLayout;
    QHBoxLayout* lastNameLayout;
    QHBoxLayout* companyLayout;

    // Labels
    QLabel* numberLabel;
    QLabel* creationLabel;
    QLabel* fromDateLabel;
    QLabel* toDateLabel;
    QLabel* lastEditLabel;
    QLabel* fromLastEditDateLabel;
    QLabel* toLastEditDateLabel;
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
    QDateEdit* fromLastEditDateEdit;
    QDateEdit* toLastEditDateEdit;

    // Buttons
    QPushButton* searchButton;

};
