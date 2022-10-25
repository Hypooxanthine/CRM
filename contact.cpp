#include "contact.h"
#include "date.h"

Contact::     Contact(const std::string& id, const std::string& name,
                      const std::string& email,const std::string& phone,
                      const std::string& photoPath, const Date& date,
                      const std::vector<Interaction> interactionList)
{
    setId(id);
    setName(name);
    setEmail(email);
    setPhone(phone);
    setPhotoPath(photoPath);
    setDate(date);
    setInteractionList(interactionList);
}

Contact::Contact(const Contact& c){
    setId(c.getId());
    setName(c.getName());
    setEmail(c.getEmail());
    setPhone(c.getPhone());
    setPhotoPath(c.getPhotoPath());
    setDate(c.getDate());
    setInteractionList(c.getInteractionList());
}

void Contact::addInteraction(Interaction interaction)
{
    Contact::interactionList.push_back(interaction);
}


std::ostream& operator<<(std::ostream& os, const Contact& c){
    os<<"{"<<
        "\"id\":\""<<c.getId()<<"\","<<
        "\"Name\":\""<<c.getName()<<"\","<<
        "\"email\":\""<<c.getEmail()<<"\","<<
        "\"phone\":\""<<c.getPhone()<<"\","<<
        "\"creationDate\":"<<c.getDate()<<
        "}";
    return os;
 }
