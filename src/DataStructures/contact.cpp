#include "DataStructures/contact.h"
#include "DataStructures/date.h"

Contact::Contact(const std::string& firstName, const std::string& lastName,
                 const std::string& company, const std::string& email,
                 const std::string& phone, const std::string& photoPath,
                 const Date& date)
{
    setFirstName(firstName);
    setLastName(lastName);
    setCompany(company);
    setEmail(email);
    setPhone(phone);
    setPhotoPath(photoPath);
    setDate(date);
}

std::ostream& operator<<(std::ostream& os, const Contact& c){
    os << "Name: " << c.getFirstName() << " " << c.getLastName() << std::endl <<
          "Company: " << c.getCompany() << std::endl <<
          "email: " << c.getEmail() << std::endl <<
          "phone: " << c.getPhone() << std::endl <<
          "creationDate: " << c.getDate() << std::endl;

    os << "Interactions: " << std::endl;

    os << c.getInteractions();
    return os;
 }

bool Contact::operator==(const Contact& other) const
{
    return  firstName == other.firstName
            && lastName == other.lastName
            && company == other.company
            && email == other.email
            && phone == other.phone
            && photoPath == other.photoPath
            && date == other.date
            && interactionList == other.interactionList;
}
