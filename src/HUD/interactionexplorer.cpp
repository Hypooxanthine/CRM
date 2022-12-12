#include "HUD/interactionexplorer.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "DataStructures/interaction.h"
#include "DataStructures/interactionmanager.h"

#include "HUD/interactionedit.h"

InteractionExplorer::InteractionExplorer(InteractionManager* interactions, QWidget *parent)
    : QWidget(parent), interactions(interactions),
      mainLayout(new QVBoxLayout()), headerLayout(new QHBoxLayout()), interactionsLayout(new QVBoxLayout()),
      titleLabel(new QLabel(tr("Interactions"), this)), addButton(new QPushButton(tr("Add"), this))
{
    // Layouts
    setLayout(mainLayout);

    mainLayout->addLayout(headerLayout);
        headerLayout->addWidget(titleLabel);
        headerLayout->addWidget(addButton);
    mainLayout->addLayout(interactionsLayout);

    QWidget::connect(addButton, SIGNAL(clicked()), this, SLOT(requestInteractionEdit()));
}

void InteractionExplorer::refreshInteractionsHUD()
{
    clearInteractionsHUD();

    for(const auto& i : *interactions)
        addInteractionHUD(i);
}

void InteractionExplorer::clearInteractionsHUD()
{
    QLayoutItem* child;

    while((child = interactionsLayout->takeAt(0)) != nullptr)
        delete child->widget();
}

void InteractionExplorer::addInteractionHUD(const Interaction& interaction)
{
    QVBoxLayout* layout = new QVBoxLayout();
    QLabel* text = new QLabel(QString::fromStdString(interaction.getContent()), this);
    QPushButton* deleteButton = new QPushButton(tr("Delete"), this);

    layout->addWidget(text);
    layout->addWidget(deleteButton);

    interactionsLayout->addLayout(layout);

    QWidget::connect(deleteButton, &QPushButton::clicked, this, [this, &interaction](){ deleteInteraction(interaction); });
}

void InteractionExplorer::addInteraction(const Interaction& interaction)
{
    interactions->add(interaction);
    refreshInteractionsHUD();
}

void InteractionExplorer::deleteInteraction(const Interaction& interaction)
{
    interactions->remove(interaction);
    refreshInteractionsHUD();
}

void InteractionExplorer::requestInteractionEdit()
{
    InteractionEdit* iEdit = new InteractionEdit(this);

    QWidget::connect(iEdit, SIGNAL(validate(Interaction)), this, SLOT(addInteraction(const Interaction&)));

    iEdit->exec();
}
