#pragma once

#include "manager.h"
#include "todo.h"

class TodoManager : public Manager<Todo>
{
public:
    TodoManager();
};
