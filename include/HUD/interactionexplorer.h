#pragma once

#include <QWidget>

#include "DataStructures/interactionmanager.h"

class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;

class Interaction;

class InteractionExplorer : public QWidget
{
    Q_OBJECT
public:
    explicit InteractionExplorer(const InteractionManager& interactions, QWidget *parent = nullptr);

    void setInteractions(const InteractionManager& interactions);

signals:
    void updated(const InteractionManager& interactions);

private: // Private methods
    void clearInteractionsHUD();
    void addInteractionHUD(const Interaction& interaction);

private slots:
    void refreshInteractionsHUD();
    void addInteraction(const Interaction& interaction);
    void deleteInteraction(const Interaction& interaction);
    void requestInteractionEdit();

private: // Private members
    InteractionManager interactions;

    // Layouts
    QVBoxLayout* mainLayout;
    QHBoxLayout* headerLayout;
    QVBoxLayout* interactionsLayout;

    // Labels
    QLabel* titleLabel;

    // Buttons
    QPushButton* addButton;
};
