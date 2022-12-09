#include "DataStructures/contact.h"
#include "DataStructures/date.h"

Contact::Contact(const std::string& firstName, const std::string& lastName,
                      const std::string& email,const std::string& phone,
                      const std::string& photoPath, const Date& date)
{
    setFirstName(firstName);
    setLastName(lastName);
    setEmail(email);
    setPhone(phone);
    setPhotoPath(photoPath);
    setDate(date);
}

std::ostream& operator<<(std::ostream& os, const Contact& c){
    os << "{" <<
        "\"Name\":\"" << c.getFirstName() << " " << c.getLastName() << "\","<<
        "\"email\":\"" << c.getEmail() << "\","<<
        "\"phone\":\"" << c.getPhone() << "\","<<
        "\"creationDate\":" << c.getDate() << "}";
    return os;
 }

bool Contact::operator==(const Contact& other) const
{
    return  firstName == other.firstName
            && lastName == other.lastName
            && email == other.email
            && phone == other.phone
            && photoPath == other.photoPath
            && date == other.date
            && interactionList == other.interactionList;
}
