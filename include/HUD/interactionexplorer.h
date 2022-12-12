#pragma once

#include <QWidget>

class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;

class InteractionManager;
class Interaction;

class InteractionExplorer : public QWidget
{
    Q_OBJECT
public:
    explicit InteractionExplorer(InteractionManager* interactions, QWidget *parent = nullptr);

signals:

private: // Private methods
    void clearInteractionsHUD();
    void addInteractionHUD(const Interaction& interaction);

private slots:
    void refreshInteractionsHUD();
    void addInteraction(const Interaction& interaction);
    void deleteInteraction(const Interaction& interaction);
    void requestInteractionEdit();

private: // Private members
    InteractionManager* interactions;

    // Layouts
    QVBoxLayout* mainLayout;
    QHBoxLayout* headerLayout;
    QVBoxLayout* interactionsLayout;

    // Labels
    QLabel* titleLabel;

    // Buttons
    QPushButton* addButton;
};
