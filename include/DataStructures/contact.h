#pragma once

#include <string>

#include "interactionmanager.h"
#include "date.h"

class Contact
{
public: //Publics methods
    friend class UnitTest;

    /**
     * @brief Has to be called for a known Contact. For example, when retrieving a Contact from the database, the Contact
     * is known, so are the other parameters.
     * @param name The name of the Contact.
     * @param email The email of the Contact.
     * @param phone The phone of the Contact.
     * @param photoPath The photo's path of the contact.
     * @param date The date the Contact was created.
     */
    Contact(const std::string& firstName, const std::string& lastName,
            const std::string& email,const std::string& phone,
            const std::string& photoPath, const Date& date);

    /**
     * @brief Default constructor constructs an empty contact.
     */
    Contact() = default;

    /**
     * @brief Has to be called to copy a Contact.
     * @param c The Contact to copy.
     */
    Contact(const Contact& c) = default;

    // Setters

    /**
     * @brief Sets the first name of the Contact.
     * @param The new first name.
     */
    inline void setFirstName(const std::string& firstName){ this->firstName = firstName; }

    /**
     * @brief Sets the last name of the Contact.
     * @param The new last name.
     */
    inline void setLastName(const std::string& lastName){ this->lastName = lastName; }

    /**
     * @brief Sets the email of the Contact.
     * @param The new email.
     */
    inline void setEmail(const std::string& email){ this->email = email; }

    /**
     * @brief Sets the phone of the Contact.
     * @param The new phone.
     */
    inline void setPhone(const std::string& phone){ this->phone = phone; }

    /**
     * @brief Sets the photo's path of the Contact.
     * @param The new photo's path.
     */
    inline void setPhotoPath(const std::string& photoPath){ this->photoPath = photoPath; }

    /**
     * @brief Sets the date of the Contact.
     * @param The new date .
     */
    inline void setDate(const Date& date){ this->date = date; }

    /**
     * @brief Sets the Contact's list of interactions.
     * @param The new Contact's list of interactions.
     */
    inline void setInteractionManager(const InteractionManager& InteractionList){ this->interactionList = InteractionList; }


    //Getters

    /**
     * @brief Gets the first name of the Contact.
     * @return The first name of the Contact.
     */
    inline const std::string& getFirstName() const { return firstName; }

    /**
     * @brief Gets the last name of the Contact.
     * @return The last name of the Contact.
     */
    inline const std::string& getLastName() const { return lastName; }

    /**
     * @brief Gets the email of the Contact.
     * @return The email of the Contact.
     */
    inline const std::string& getEmail() const { return email; }

    /**
     * @brief Gets the phone of the Contact.
     * @return The phone of the contact.
     */
    inline const std::string& getPhone() const { return phone; }

    /**
     * @brief Gets the photo's path of the Contact.
     * @return The photo's path of the Contact.
     */
    inline const std::string& getPhotoPath() const { return photoPath; }

    /**
     * @brief Gets the date of the Contact.
     * @return The date of the Contact.
     */
    inline const Date& getDate() const { return date; }

    /**
     * @brief Gets the Contact's list of interactions.
     * @return A const reference to the Contact's list of interactions.
     */
    inline const InteractionManager& getInteractions() const { return interactionList; }

    /**
     * @brief Gets the Contact's list of interactions.
     * @return A reference to the Contact's list of interactions.
     */
    inline InteractionManager& getInteractions() { return interactionList; }

    friend std::ostream& operator<<(std::ostream& os, const Contact& c);

    /**
     * @brief Compare operator.
     * @param other The Contact to compare to.
     * @return A boolean. True : all fields are the same. False otherwise.
     */
    bool operator==(const Contact& other) const;

private: // Private memebers
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string phone;
    std::string photoPath;
    Date date;
    InteractionManager interactionList;
};


