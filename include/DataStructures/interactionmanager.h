#pragma once

#include "manager.h"
#include "interaction.h"

class InteractionManager : public Manager<Interaction>
{
public:
    InteractionManager() = default;
    InteractionManager(const InteractionManager&) = default;
    InteractionManager(InteractionManager&&) = default;
    InteractionManager& operator=(const InteractionManager&) = default;
};
