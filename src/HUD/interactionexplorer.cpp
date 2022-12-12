#include "HUD/interactionexplorer.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "DataStructures/interaction.h"
#include "DataStructures/interactionmanager.h"

#include "HUD/interactionedit.h"

InteractionExplorer::InteractionExplorer(const InteractionManager& interactions, QWidget *parent)
    : QWidget(parent), interactions(interactions),
      mainLayout(new QVBoxLayout()), headerLayout(new QHBoxLayout()), interactionsLayout(new QVBoxLayout()),
      titleLabel(new QLabel(tr("Interactions"), this)), addButton(new QPushButton(tr("New interaction"), this))
{
    // Layouts
    setLayout(mainLayout);

    mainLayout->addLayout(headerLayout);
        headerLayout->addWidget(titleLabel, 9);
        headerLayout->addWidget(addButton, 1);
    mainLayout->addLayout(interactionsLayout);

    QWidget::connect(addButton, SIGNAL(clicked()), this, SLOT(requestInteractionEdit()));
}

void InteractionExplorer::setInteractions(const InteractionManager &interactions)
{
    this->interactions = interactions;
    refreshInteractionsHUD();
}

void InteractionExplorer::refreshInteractionsHUD()
{
    clearInteractionsHUD();

    for(const auto& i : interactions)
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
    QLabel* text = new QLabel(QString::fromStdString(interaction.getContent()));
    QPushButton* deleteButton = new QPushButton(tr("Delete"));

    text->setStyleSheet("border: 1px solid black");

    layout->setAlignment(Qt::AlignLeft);

    layout->addWidget(text);
    layout->addWidget(deleteButton);

    interactionsLayout->addLayout(layout);

    QWidget::connect(deleteButton, &QPushButton::clicked, this, [this, &interaction](){ deleteInteraction(interaction); });
}

void InteractionExplorer::addInteraction(const Interaction& interaction)
{
    interactions.add(interaction);
    emit updated(interactions);
    refreshInteractionsHUD();
}

void InteractionExplorer::deleteInteraction(const Interaction& interaction)
{
    interactions.remove(interaction);
    emit updated(interactions);
    refreshInteractionsHUD();
}

void InteractionExplorer::requestInteractionEdit()
{
    InteractionEdit* iEdit = new InteractionEdit(this);

    QWidget::connect(iEdit, SIGNAL(validate(Interaction)), this, SLOT(addInteraction(const Interaction&)));

    iEdit->exec();
}
