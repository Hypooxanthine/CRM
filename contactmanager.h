#pragma once

#include "manager.h"
#include "contact.h"

class ContactManager : public Manager<Contact>
{
public:
    ContactManager();
};

