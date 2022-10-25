#pragma once

#include<string>
#include <iostream>
#include<vector>
#include<interaction.h>

class Contact
{



private:

    std::string id;
    std::string Name;
    std::string email;
    std::string phone;
    std::string photo;
    unsigned creationDate;
    std::vector<Interaction> interactionList;

public:


    Contact(const std::string& id, const std::string& name,
            const std::string& email,const std::string& phone,
            const std::string& photo, const unsigned cDate,
            const std::vector<Interaction> interactionList );


    Contact(const Contact& c);


    Contact();
    ~Contact();

    //getters and setters
    std::string getId() const;
    void setId(const std::string &newId);

    std::string getName() const;
    void setName(const std::string &newName);

    std::string getEmail() const;
    void setEmail(const std::string &newEmail);

    std::string getPhone() const;
    void setPhone(const std::string &newPhone);

    std::string getPhoto() const;
    void setPhoto(const std::string &newPhoto);

    unsigned getCreationDate() const;
    void setCreationDate(const unsigned &newCreationDate);

    std::vector<Interaction> getInteractionList() const;
    void setInteractionList(const std::vector<Interaction> &newInteractionList );



    friend std::ostream& operator<<(std::ostream& os, const Contact& c);

};


