#include "HUD/contactsearch.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDateEdit>
#include <QPushButton>

ContactSearch::ContactSearch(QWidget *parent)
    : QWidget(parent),
      // Layouts
      mainLayout(new QHBoxLayout()),
      numberLayout(new QHBoxLayout()),
      creationLayout(new QHBoxLayout()),
      creationDatesLayout(new QVBoxLayout()),
      fromDateLayout(new QHBoxLayout()),
      toDateLayout(new QHBoxLayout()),
      lastEditLayout(new QHBoxLayout()),
      lastEditDatesLayout(new QVBoxLayout()),
      fromLastEditDateLayout(new QHBoxLayout()),
      toLastEditDateLayout(new QHBoxLayout()),
      nameLayout(new QVBoxLayout()),
      firstNameLayout(new QHBoxLayout()),
      lastNameLayout(new QHBoxLayout()),
      companyLayout(new QHBoxLayout()),

      // Labels
      numberLabel(new QLabel(tr("Contacts number"), this)),
      creationLabel(new QLabel(tr("Creation date"), this)),
      fromDateLabel(new QLabel(tr("from"), this)),
      toDateLabel(new QLabel(tr("to"), this)),
      lastEditLabel(new QLabel(tr("Last edit date"), this)),
      fromLastEditDateLabel(new QLabel(tr("from"), this)),
      toLastEditDateLabel(new QLabel(tr("to"), this)),
      firstNameLabel(new QLabel(tr("First name"), this)),
      lastNameLabel(new QLabel(tr("Last name"), this)),
      companyLabel(new QLabel(tr("Company name"), this)),

      // Line edits
      firstNameEdit(new QLineEdit(this)),
      lastNameEdit(new QLineEdit(this)),
      companyEdit(new QLineEdit(this)),

      // Spin boxes
      numberSpin(new QSpinBox(this)),

      // Date edits
      fromDateEdit(new QDateEdit(QDate::currentDate().addDays(-6), this)),
      toDateEdit(new QDateEdit(QDate::currentDate(), this)),
      fromLastEditDateEdit(new QDateEdit(QDate::currentDate().addDays(-6), this)),
      toLastEditDateEdit(new QDateEdit(QDate::currentDate(), this)),

      // Buttons
      searchButton(new QPushButton(tr("Search"), this))
{
    // Layouts hierarchy
    setLayout(mainLayout);
    mainLayout->addLayout(numberLayout);
        numberLayout->addWidget(numberLabel);
        numberLayout->addWidget(numberSpin);
    mainLayout->addLayout(nameLayout);
        nameLayout->addLayout(firstNameLayout);
            firstNameLayout->addWidget(firstNameLabel);
            firstNameLayout->addWidget(firstNameEdit);
        nameLayout->addLayout(lastNameLayout);
            lastNameLayout->addWidget(lastNameLabel);
            lastNameLayout->addWidget(lastNameEdit);
    mainLayout->addLayout(companyLayout);
        companyLayout->addWidget(companyLabel);
        companyLayout->addWidget(companyEdit);
    mainLayout->addLayout(creationLayout);
        creationLayout->addWidget(creationLabel);
        creationLayout->addLayout(creationDatesLayout);
            creationDatesLayout->addLayout(fromDateLayout);
                fromDateLayout->addWidget(fromDateLabel);
                fromDateLayout->addWidget(fromDateEdit);
            creationDatesLayout->addLayout(toDateLayout);
                toDateLayout->addWidget(toDateLabel);
                toDateLayout->addWidget(toDateEdit);
    mainLayout->addLayout(lastEditLayout);
        lastEditLayout->addWidget(lastEditLabel);
        lastEditLayout->addLayout(lastEditDatesLayout);
            lastEditDatesLayout->addLayout(fromLastEditDateLayout);
                fromLastEditDateLayout->addWidget(fromLastEditDateLabel);
                fromLastEditDateLayout->addWidget(fromLastEditDateEdit);
            lastEditDatesLayout->addLayout(toLastEditDateLayout);
                toLastEditDateLayout->addWidget(toLastEditDateLabel);
                toLastEditDateLayout->addWidget(toLastEditDateEdit);
    mainLayout->addWidget(searchButton);

    // Widgets initialization
    numberSpin->setValue(10);
    numberSpin->setMinimum(0);

    // Connexions
    QWidget::connect(searchButton, SIGNAL(clicked()), this, SIGNAL(searched()));
}

QString ContactSearch::getFirstName() const
{
    return firstNameEdit->text();
}

QString ContactSearch::getLastName() const
{
    return lastNameEdit->text();
}

QString ContactSearch::getCompany() const
{
    return companyEdit->text();
}

int ContactSearch::getContactsNumber() const
{
    return numberSpin->value();
}

QDate ContactSearch::getFromDate() const
{
    return fromDateEdit->date();
}

QDate ContactSearch::getToDate() const
{
    return toDateEdit->date();
}

QDate ContactSearch::getFromLastEditDate() const
{
    return fromLastEditDateEdit->date();
}
QDate ContactSearch::getToLastEditDate() const
{
    return toLastEditDateEdit->date();
}
