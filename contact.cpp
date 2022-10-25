#include "contact.h"

Contact::     Contact(const std::string& id, const std::string& name,
                      const std::string& email,const std::string& phone,
                      const std::string& photo, const unsigned cDate,
                      const std::vector<Interaction> interactionList)
{

    setId(id);
    setName(name);
    setEmail(email);
    setPhone(phone);
    setPhoto(photo);
    setCreationDate(cDate);
    setInteractionList(interactionList);

}

Contact::Contact(const Contact& c){
    setId(c.getId());
    setName(c.getName());
    setEmail(c.getEmail());
    setPhone(c.getPhone());
    setPhoto(c.getPhoto());
    setCreationDate(c.getCreationDate());
    setInteractionList(c.getInteractionList());
}

Contact::Contact(){}
Contact::~Contact(){}


void Contact::setId(const std::string& id){ this->id = id;}
void Contact::setName(const std::string& name){this->Name = name;}
void Contact::setEmail(const std::string& email){this->email = email;}
void Contact::setPhone(const std::string& phone){this->phone = phone;}
void Contact::setPhoto(const std::string& photo){this->photo = photo;}
void Contact::setCreationDate(const unsigned& cDate){this->creationDate = cDate;}
void Contact::setInteractionList(const std::vector<Interaction> &newInteractionList){this->interactionList =newInteractionList;}

std::string Contact::getId() const {return this->id;}
std::string Contact::getName() const {return this->Name;}
std::string Contact::getEmail() const {return this->email;}
std::string Contact::getPhone() const {return this->phone;}
std::string Contact::getPhoto() const {return this->photo;}
unsigned Contact::getCreationDate() const {return this->creationDate;}
std::vector<Interaction> Contact::getInteractionList() const {return this->interactionList;}


std::ostream& operator<<(std::ostream& os, const Contact& c){
    os<<"{"<<
        "\"id\":\""<<c.getId()<<"\","<<
        "\"Name\":\""<<c.getName()<<"\","<<
        "\"email\":\""<<c.getEmail()<<"\","<<
        "\"phone\":\""<<c.getPhone()<<"\","<<
        "\"creationDate\":"<<c.getCreationDate()<<
        "}";
    return os;
 }
