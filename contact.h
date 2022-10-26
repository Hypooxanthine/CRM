#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "interaction.h"
#include "date.h"

class Contact
{
public: //Publics methods
    friend class UnitTest;
    /**
     * @brief Default constructor is deleted.
     */
    Contact() = delete;

    /**
     * @brief Has to be called for a known Contact.For example, when retrieving a Contact from the database, the Contact
     * is known, so are the other parameters.
     * @param id The id of the Contact.
     * @param name The name of the Contact.
     * @param email The email of the Contact.
     * @param phone The phone of the Contact.
     * @param photoPath The photo's path of the contact.
     * @param date The date the Contact was created.
     * @param interactionList The Contact's list of interactions.
     */
    Contact(const std::string& id, const std::string& name,
            const std::string& email,const std::string& phone,
            const std::string& photoPath, const Date& date,
            const std::vector<Interaction> interactionList );

    /**
     * @brief Has to be called to copy a Contact.
     * @param c The Contact to copy.
     */
    Contact(const Contact& c);

    // Setters
    /**
     * @brief Sets the id of the Contact.
     * @param The new id.
     */
    inline void setId(const std::string& id){ this->id = id;}

    /**
     * @brief Sets the Name of the Contact.
     * @param The new name.
     */
    inline void setName(const std::string& name){this->Name = name;}

    /**
     * @brief Sets the email of the Contact.
     * @param The new email.
     */
    inline void setEmail(const std::string& email){this->email = email;}

    /**
     * @brief Sets the phone of the Contact.
     * @param The new phone.
     */
    inline void setPhone(const std::string& phone){this->phone = phone;}

    /**
     * @brief Sets the photo's path of the Contact.
     * @param The new photo's path.
     */
    inline void setPhotoPath(const std::string& photoPath){this->photoPath = photoPath;}

    /**
     * @brief Sets the date of the Contact.
     * @param The new date .
     */
    inline void setDate(const Date& date){this->date = date;}

    /**
     * @brief Sets the Contact's list of interactions.
     * @param The new Contact's list of interactions.
     */
    inline void setInteractionList(const std::vector<Interaction>& InteractionList){this->interactionList = InteractionList;}


    //Getters

    /**
     * @brief Gets the id of the Contact.
     * @return The id of the Contact.
     */
    inline const std::string getId() const {return id;}

    /**
     * @brief Gets the Name of the Contact.
     * @return The Name of the Contact.
     */
    inline const std::string getName() const {return Name;}

    /**
     * @brief Gets the email of the Contact.
     * @return The email of the Contact.
     */
    inline const std::string getEmail() const {return email;}

    /**
     * @brief Gets the phone of the Contact.
     * @return The phone of the contact.
     */
    inline const std::string getPhone() const {return phone;}

    /**
     * @brief Gets the photo's path of the Contact.
     * @return The photo's path of the Contact.
     */
    inline const std::string getPhotoPath() const {return photoPath;}

    /**
     * @brief Gets the date of the Contact.
     * @return The date of the Contact.
     */
    inline const Date getDate() const {return date;}

    /**
     * @brief Gets the Contact's list of interactions.
     * @return The Contact's list of interactions.
     */
    inline const std::vector<Interaction> getInteractionList() const {return interactionList;}


    /**
     * @brief Add an interaction to the Contact's list of interactions.
     * @param interaction to add to the list.
     */
    void addInteraction(Interaction interaction);

    friend std::ostream& operator<<(std::ostream& os, const Contact& c);

private: // Private memebers
    std::string id;
    std::string Name;
    std::string email;
    std::string phone;
    std::string photoPath;
    Date date;
    std::vector<Interaction> interactionList;
};


