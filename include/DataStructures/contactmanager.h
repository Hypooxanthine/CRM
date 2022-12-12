#pragma once

#include "manager.h"
#include "contact.h"

class ContactManager : public Manager<Contact>
{
public:
    enum class SortValue
    {
        FirstName = 0, LastName, Company, Phone, Email, CreationDate, LastEditDate,
    };

    enum class SortType
    {
        Ascending = 0, Descending,
    };

public:
    ContactManager() = default;
    ContactManager(const ContactManager&) = default;
    ContactManager(ContactManager&&) = default;
    ContactManager& operator=(const ContactManager&) = default;

    void sort(const SortValue& sortValue, const SortType& sortType);

    ContactManager extractHeadNumber(const size_t& nb);
    ContactManager extractByFirstName(const std::string& firstName);
    ContactManager extractByLastName(const std::string lastName);
    ContactManager extractByCompany(const std::string& company);
    ContactManager extractByCreationDate(const Date& first, const Date& second);
    ContactManager extractByLastEditDate(const Date& first, const Date& second);

    inline const std::optional<Date>& getLastDeletionDate() const { return lastDeletionDate; }
    inline void setLastDeletionDate(const Date& d) { lastDeletionDate = d; }

private:
    std::optional<Date> lastDeletionDate;
};

