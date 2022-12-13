#include "HUD/Todos/todoexplorer.h"

#include <map>
#include <tuple>

#include <QVBoxLayout>
#include <QScrollArea>

#include "DataStructures/contactmanager.h"
#include "DataStructures/todo.h"

#include "HUD/Todos/todoentry.h"

TodoExplorer::TodoExplorer(ContactManager* contacts, QWidget *parent)
    : QWidget(parent), contacts(contacts),
      mainLayout(new QVBoxLayout()), explorerLayout(new QVBoxLayout()), todosArea(new QScrollArea(this))
{
    setLayout(mainLayout);
    explorerLayout->setAlignment(Qt::AlignTop);
    explorerLayout->setMargin(0);
    explorerLayout->setContentsMargins(0, 0, 0, 0);
    explorerLayout->setSizeConstraint(QLayout::SetMinimumSize);

    // Scroll area
    QWidget* scrollWidget = new QWidget();
    scrollWidget->setLayout(explorerLayout);
    todosArea->setWidget(scrollWidget);
    todosArea->setWidgetResizable(true);

    mainLayout->addWidget(todosArea);

    refresh();
}

void TodoExplorer::refresh()
{
    QLayoutItem* child = nullptr;

    while((child = explorerLayout->takeAt(0)) != nullptr)
        delete child->widget();

    std::list<std::tuple<Contact*, Interaction*, Todo*>> sortedTodos;

    for(Contact& c : *contacts)
    {
        for(Interaction& i : c.getInteractions())
        {
            for(Todo& t : i.getTodos())
            {
                sortedTodos.push_back(std::make_tuple(&c, &i, &t));
            }
        }
    }

    sortedTodos.sort([](const std::tuple<Contact*, Interaction*, Todo*>& a, const std::tuple<Contact*, Interaction*, Todo*>& b)
    {
        return std::get<2>(a)->getDate() < std::get<2>(b)->getDate();
    });

    for(const auto& tuple : sortedTodos)
        addTodoEntry(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple));
}

void TodoExplorer::addTodoEntry(Contact* contact, Interaction* interaction, Todo* todo)
{
    TodoEntry* entry = new TodoEntry(todo, interaction, contact, this);

    explorerLayout->addWidget(entry);

    QWidget::connect(entry, SIGNAL(deleted(Contact*, Interaction*, Todo*)), this, SLOT(removeTodo(Contact*, Interaction*, Todo*)));
}

void TodoExplorer::removeTodo(Contact* c, Interaction* i, Todo* t)
{
    auto cIt = contacts->find(*c);
    if(cIt == contacts->end()) return;

    auto iIt = cIt->getInteractions().find(*i);
    if(iIt == cIt->getInteractions().end()) return;

    auto tIt = iIt->getTodos().find(*t);
    if(tIt == iIt->getTodos().end()) return;

    iIt->getTodos().remove(*tIt);

    refresh();
}
