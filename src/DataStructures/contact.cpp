#include "DataStructures/contact.h"
#include "DataStructures/date.h"

Contact::Contact(const size_t& id, const std::string& name,
                      const std::string& email,const std::string& phone,
                      const std::string& photoPath, const Date& date)
{
    setId(id);
    setName(name);
    setEmail(email);
    setPhone(phone);
    setPhotoPath(photoPath);
    setDate(date);
}

Contact::Contact(const Contact& c)
{
    setId(c.getId());
    setName(c.getName());
    setEmail(c.getEmail());
    setPhone(c.getPhone());
    setPhotoPath(c.getPhotoPath());
    setDate(c.getDate());
    setInteractionManager(c.getInteractionManager());
}

std::ostream& operator<<(std::ostream& os, const Contact& c){
    os << "{" <<
        "\"id\":\"" << c.getId() << "\","<<
        "\"Name\":\"" << c.getName() << "\","<<
        "\"email\":\"" << c.getEmail() << "\","<<
        "\"phone\":\"" << c.getPhone() << "\","<<
        "\"creationDate\":" << c.getDate() << "}";
    return os;
 }

bool Contact::operator==(const Contact& other) const
{
    return id == other.id
            && name == other.name
            && email == other.email
            && phone == other.phone
            && photoPath == other.photoPath
            && date == other.date
            && interactionList == other.interactionList;
}
