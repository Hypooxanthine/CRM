#include "HUD/contactedit.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QDir>
#include <QPixmap>

#include "HUD/interactionexplorer.h"

ContactEdit::ContactEdit(const QString& windowTitle, QWidget *parent)
    : QWidget(parent),
      // Scrolling
      scrollLayout(new QVBoxLayout()), scrollArea(new QScrollArea()),

      // Layouts
      mainLayout(new QVBoxLayout()), form(new QFormLayout()),
      photoLayout(new QHBoxLayout()), buttonsLayout(new QHBoxLayout()),

      // Labels
      photoImgLabel(new QLabel()),

      // Line edits
      firstNameEdit(new QLineEdit(this)), lastNameEdit(new QLineEdit(this)), companyEdit(new QLineEdit(this)),
      emailEdit(new QLineEdit(this)), phoneEdit(new QLineEdit(this)), photoEdit(new QLineEdit(this)),

      // Buttons
      photoFileButton(new QPushButton(tr("Browse"), this)),
      cancelButton(new QPushButton(tr("Cancel"), this)), validateButton(new QPushButton(tr("OK"), this)),

      // Interactions
      interactionsExplorer(new InteractionExplorer(this))
{
    // Window
    setWindowTitle(windowTitle);

    // Layouts
    mainLayout->addLayout(form);
    mainLayout->addWidget(interactionsExplorer);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setMargin(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);

    form->addRow(tr("First name"), firstNameEdit);
    form->addRow(tr("Last name"), lastNameEdit);
    form->addRow(tr("Company"), companyEdit);
    form->addRow(tr("Email"), emailEdit);
    form->addRow(tr("Phone number"), phoneEdit);
    form->addRow(tr("Photo path"), photoLayout);

    photoLayout->addWidget(photoImgLabel);
    photoLayout->addWidget(photoEdit);
    photoLayout->addWidget(photoFileButton);

    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->addWidget(validateButton);

    buttonsLayout->setAlignment(Qt::AlignRight);

    setLayout(scrollLayout);

    // Buttons
    photoFileButton->setAutoDefault(false);
    validateButton->setDefault(true);

    // Scrolling
    scrollLayout->addWidget(scrollArea);
    QWidget* scrollWidget = new QWidget();
    scrollWidget->setLayout(mainLayout);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);

    // Connexions
    QWidget::connect(photoEdit, SIGNAL(textChanged(const QString&)), this, SLOT(updatePhotoImg()));
    QWidget::connect(photoFileButton, SIGNAL(clicked()), this, SLOT(getPhotoFromFile()));
    QWidget::connect(validateButton, SIGNAL(clicked()), this, SLOT(onValidate()));
    QWidget::connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    QWidget::connect(firstNameEdit, SIGNAL(returnPressed()), this, SLOT(onValidate()));
    QWidget::connect(lastNameEdit, SIGNAL(returnPressed()), this, SLOT(onValidate()));
    QWidget::connect(companyEdit, SIGNAL(returnPressed()), this, SLOT(onValidate()));
    QWidget::connect(emailEdit, SIGNAL(returnPressed()), this, SLOT(onValidate()));
    QWidget::connect(phoneEdit, SIGNAL(returnPressed()), this, SLOT(onValidate()));
    QWidget::connect(photoEdit, SIGNAL(returnPressed()), this, SLOT(onValidate()));
}

ContactEdit::ContactEdit(const Contact& contact, const QString& windowTitle, QWidget* parent)
    : ContactEdit(windowTitle, parent)
{
    setContact(contact);
}

void ContactEdit::setContact(const Contact &contact)
{
    firstNameEdit->setText(QString::fromStdString(contact.getFirstName()));
    lastNameEdit->setText(QString::fromStdString(contact.getLastName()));
    companyEdit->setText(QString::fromStdString(contact.getCompany()));
    emailEdit->setText(QString::fromStdString(contact.getEmail()));
    phoneEdit->setText(QString::fromStdString(contact.getPhone()));
    photoEdit->setText(QString::fromStdString(contact.getPhotoPath()));
}

void ContactEdit::onValidate()
{
    Contact out;

    out.setFirstName(firstNameEdit->text().toStdString());
    out.setLastName(lastNameEdit->text().toStdString());
    out.setCompany(companyEdit->text().toStdString());
    out.setEmail(emailEdit->text().toStdString());
    out.setPhone(phoneEdit->text().toStdString());
    out.setPhotoPath(photoEdit->text().toStdString());
    out.setDate(Date::today());

    emit validate(out);

    this->close();
}

void ContactEdit::getPhotoFromFile()
{
    auto path = QFileDialog::getOpenFileName(this, tr("Open image"), QDir::currentPath());

    photoEdit->setText(path);
}

void ContactEdit::updatePhotoImg()
{
    QImage* img = new QImage(photoEdit->text());

    if(img->isNull())
        photoImgLabel->clear();
    else
        photoImgLabel->setPixmap(QPixmap::fromImage(*img));

}
