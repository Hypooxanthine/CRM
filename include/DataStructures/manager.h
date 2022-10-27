#pragma once

#include <list>
#include <cstddef>
#include <iostream>

template <typename T>
class Manager
{
public:
    using iterator = typename std::list<T>::iterator;
    using const_iterator = typename std::list<T>::const_iterator;
public:
    friend class UnitTest;

    Manager() {}

    /**
     * @brief Adds an element to the Manager.
     * @param element A const reference to the element to add.
     */
    void add(const T& element)
    {
        data.push_back(element);
    }

    /**
     * @brief Adds an element to the Manager.
     * @param element An rvalue of the element to add.
     */
    void add(T&& element)
    {
        data.push_back(std::move(element));
    }

    /**
     * @brief Removes an element from the Manager.
     * @param element A const reference to the element.
     */
    void remove(const T& element)
    {
        data.remove(element);
    }

    /**
     * @brief Gets the front element.
     * @return A reference to the front element.
     */
    T& getFront()
    {
        return data.front();
    }

    /**
     * @brief Gets the front element.
     * @return A const reference to the front element.
     */
    const T& getFront() const
    {
        return data.front();
    }

    /**
     * @brief Gets the back element.
     * @return A reference to the back element.
     */
    T& getBack()
    {
        return data.back();
    }

    /**
     * @brief Gets the back element.
     * @return A const reference to the back element.
     */
    const T& getBack() const
    {
        return data.back();
    }

    /**
     * @brief Gets the number of elements of the Manager.
     * @return The number of elements of the Manager.
     */
    inline size_t getSize() const { return data.size(); }

    /**
     * @brief Checks if the Manager is empty or not.
     * @return A boolean : true if empty, false if not.
     */
    inline bool isEmpty() const { return getSize() == 0; }

    // Iterators
    /**
     * @brief Gets an iterator to the front element.
     * @return An iterator to the front element.
     */
    iterator begin() { return data.begin(); }

    /**
     * @brief Gets a reverse iterator to the front element.
     * @return A reverse iterator to the front element.
     */
    iterator rbegin() { return data.rbegin(); }

    /**
     * @brief Gets an iterator to the back element.
     * @return An iterator to the back element.
     */
    iterator end() { return data.end(); }

    /**
     * @brief Gets a reverse iterator to the back element.
     * @return A reverse iterator to the back element.
     */
    iterator rend() { return data.rend(); }

    /**
     * @brief Gets a const iterator to the front element.
     * @return A const iterator to the front element.
     */
    const_iterator begin() const { return data.begin(); }

    /**
     * @brief Gets a const reverse iterator to the front element.
     * @return A const reverse iterator to the front element.
     */
    const_iterator rbegin() const { return data.rbegin(); }

    /**
     * @brief Gets a const iterator to the back element.
     * @return A const iterator to the back element.
     */
    const_iterator end() const { return data.end(); }

    /**
     * @brief Gets a const reverse iterator to the back element.
     * @return A const reverse iterator to the back element.
     */
    const_iterator rend() const { return data.rend(); }

    /**
     * @brief Compare operator.
     * @param other The Manager to compare to.
     * @return A boolean. True : all elements in data are the same. False otherwise.
     */
    bool operator==(const Manager<T>& other) const
    {
        return data == other.data;
    }

    friend std::ostream& operator<<(std::ostream& os, const Manager<T>& other)
    {
        auto it = other.begin();

        while(it != other.end())
        {
            os << *it;
            if(++it != other.end())
                os << std::endl;
        }

        return os;
    }

private:
    std::list<T> data;
};

