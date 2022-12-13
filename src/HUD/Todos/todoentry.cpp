#include "HUD/Todos/todoentry.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "DataStructures/todo.h"
#include "DataStructures/interaction.h"
#include "DataStructures/contact.h"

TodoEntry::TodoEntry(Todo* todo, Interaction* interaction, Contact* contact, QWidget *parent)
    : QWidget(parent), todo(todo), interaction(interaction), contact(contact),
      mainLayout(new QHBoxLayout()),
      text(new QLabel(this)), date(new QLabel(this)), deleteButton(new QPushButton(this))
{
    setLayout(mainLayout);
    mainLayout->addWidget(text, 6);
    mainLayout->addWidget(date, 2);
    mainLayout->addWidget(deleteButton, 2);

    text->setText(QString::fromStdString(todo->getContent()));
    text->setWordWrap(true);
    text->setAlignment(Qt::AlignJustify | Qt::AlignLeft | Qt::AlignTop);

    date->setText(QString::fromStdString(static_cast<std::string>(todo->getDate())));
    deleteButton->setText(tr("Delete"));

    deleteButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

    QWidget::connect(deleteButton, &QPushButton::clicked, this, [this](){ emit deleted(this->contact, this->interaction, this->todo); });
}
