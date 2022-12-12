#include "DataStructures/contactmanager.h"

void ContactManager::sort(const SortValue& sortValue, const SortType& sortType)
{
    switch(sortValue)
    {
    case SortValue::CreationDate:
        if(sortType == SortType::Ascending)
            data.sort([](const Contact& a, const Contact& b){ return a.getDate() < b.getDate(); });
        else
            data.sort([](const Contact& a, const Contact& b){ return a.getDate() > b.getDate(); });
        break;
    case SortValue::Email:
        if(sortType == SortType::Ascending)
            data.sort([](const Contact& a, const Contact& b){ return a.getEmail() < b.getEmail(); });
        else
            data.sort([](const Contact& a, const Contact& b){ return a.getEmail() > b.getEmail(); });
        break;
    case SortValue::FirstName:
        if(sortType == SortType::Ascending)
            data.sort([](const Contact& a, const Contact& b){ return a.getFirstName() < b.getFirstName(); });
        else
            data.sort([](const Contact& a, const Contact& b){ return a.getFirstName() > b.getFirstName(); });
        break;
    case SortValue::LastName:
        if(sortType == SortType::Ascending)
            data.sort([](const Contact& a, const Contact& b){ return a.getLastName() < b.getLastName(); });
        else
            data.sort([](const Contact& a, const Contact& b){ return a.getLastName() > b.getLastName(); });
        break;
    case SortValue::Company:
        if(sortType == SortType::Ascending)
            data.sort([](const Contact& a, const Contact& b){ return a.getCompany() < b.getCompany(); });
        else
            data.sort([](const Contact& a, const Contact& b){ return a.getCompany() > b.getCompany(); });
        break;
    case SortValue::Phone:
        if(sortType == SortType::Ascending)
            data.sort([](const Contact& a, const Contact& b){ return a.getPhone() > b.getPhone(); });
        else
            data.sort([](const Contact& a, const Contact& b){ return a.getPhone() < b.getPhone(); });
        break;
    default:
        break;
    }
}

ContactManager ContactManager::extractHeadNumber(const size_t& nb)
{
    ContactManager out;

    for(auto it = data.begin() ; it != data.end() && out.getSize() < nb ; it++)
        out.add(*it);

    return out;
}

ContactManager ContactManager::extractByFirstName(const std::string& firstName)
{
    ContactManager out;

    for(const auto& c : data)
    {
        if(c.getFirstName().find(firstName) != std::string::npos)
            out.add(c);
    }

    return out;
}

ContactManager ContactManager::extractByLastName(const std::string lastName)
{
    ContactManager out;

    for(const auto& c : data)
    {
        if(c.getLastName().find(lastName) != std::string::npos)
            out.add(c);
    }

    return out;
}

ContactManager ContactManager::extractByCompany(const std::string& company)
{
    ContactManager out;

    for(const auto& c : data)
    {
        if(c.getCompany().find(company) != std::string::npos)
            out.add(c);
    }

    return out;
}

ContactManager ContactManager::extractByCreationDate(const Date& first, const Date& second)
{
    ContactManager out;

    for(const auto& c : data)
    {
        if(c.getDate() >= first && c.getDate() <= second)
            out.add(c);
    }

    return out;
}
