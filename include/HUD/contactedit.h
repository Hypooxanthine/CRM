#pragma once

#include <QWidget>

#include "DataStructures/contact.h"

class QVBoxLayout;
class QHBoxLayout;
class QScrollArea;
class QFormLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class InteractionExplorer;

class ContactEdit : public QWidget
{
    Q_OBJECT
public: // Public methods
    explicit ContactEdit(const QString& windowTitle, QWidget* parent = nullptr);
    explicit ContactEdit(Contact& contact, const QString& windowTitle = tr("Contact Edit"), QWidget* parent = nullptr);

    void setContact(Contact& contact);

signals:
    void validate(Contact contact);

private slots:
    void onValidate();
    void getPhotoFromFile();
    void updatePhotoImg();

private: // Private members
    Contact contact;

    // Scrolling
    QVBoxLayout* scrollLayout;
    QScrollArea* scrollArea;

    // Layouts
    QVBoxLayout* mainLayout;
    QFormLayout* form;
    QHBoxLayout* photoLayout, * buttonsLayout;

    // Labels
    QLabel* photoImgLabel;

    // Line edits
    QLineEdit* firstNameEdit, * lastNameEdit, * companyEdit, * emailEdit, * phoneEdit, * photoEdit;

    // Buttons
    QPushButton* photoFileButton;
    QPushButton* cancelButton, * validateButton;

    // Interactions
    InteractionExplorer* interactionsExplorer;
};

