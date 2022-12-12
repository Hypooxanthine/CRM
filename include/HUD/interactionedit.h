#pragma once

#include <QDialog>

#include "DataStructures/interaction.h"

class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class QTextEdit;

class InteractionEdit : public QDialog
{
    Q_OBJECT
public:
    explicit InteractionEdit(QWidget *parent = nullptr);

signals:
    void validate(Interaction interaction);

private slots:
    void onValidate();

private: // Private members
    // Layouts
    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;

    // Text edition
    QTextEdit* textEdit;

    // Buttons
    QPushButton* cancelButton, * validateButton;
};
