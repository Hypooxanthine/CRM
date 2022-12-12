#include "HUD/interactionedit.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>

InteractionEdit::InteractionEdit(QWidget *parent)
    : QDialog(parent),
      mainLayout(new QVBoxLayout()), buttonsLayout(new QHBoxLayout()),
      textEdit(new QTextEdit(this)),
      cancelButton(new QPushButton(tr("Cancel"), this)), validateButton(new QPushButton(tr("OK"), this))
{
    setWindowTitle(tr("Interaction creation"));

    // Layouts
    setLayout(mainLayout);
    mainLayout->addWidget(textEdit);
    mainLayout->addLayout(buttonsLayout);
        buttonsLayout->addWidget(cancelButton);
        buttonsLayout->addWidget(validateButton);


    QWidget::connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    QWidget::connect(validateButton, SIGNAL(clicked()), this, SLOT(onValidate()));
}

void InteractionEdit::onValidate()
{
    Interaction out(textEdit->toPlainText().toStdString());

    emit validate(out);

    close();
}
