/**
 * @file User.h
 * @brief Declaration of the User class
*/

#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#include "Wallet.h"
#include "SecurityManager.h"

class Wallet;

/**
 * @class User
 * @brief Represents a user in the voting system
*/
class User
{
private:
    int userID; /**< The ID of the user */
    std::string personalData; /**< The personal data of the user */
    std::unique_ptr<Wallet> wallet; /**< The wallet of the user */
    static std::unordered_map<int, std::string> registeredUsers; /**< Static map of registered users */
    bool loggedIn; /**< Indicates if the user is logged in */

public:
    /**
     * @brief Constructor for the User class
     * 
     * Initializes a user with a given ID and personal data
     * 
     * @param id The user ID
     * @param data The personal data of the user
    */
    User(int id, const std::string& data);

    /**
     * @brief Registers the user by encrypting their personal data
    */
    void registerUser();

    /**
     * @brief Logs in the user
     * 
     * @return True if login is successful, false otherwise
    */
    bool login();

    /**
     * @brief Logs out the user
    */
    void logout();

    /**
     * @brief Checks if the user is logged in
     * 
     * @return True if the user is logged in, false otherwise
    */
    bool isLoggedIn() const;

    /**
     * @brief Gets the user ID
     * 
     * @return The user ID
    */
    int getUserID() const;

    /**
     * @brief Gets the user's wallet
     * 
     * @return Reference to the user's wallet
    */
    Wallet& getWallet();

    /**
     * @brief Checks if the user has a valid voting token
     * 
     * @return True if the user has a valid voting token, false otherwise
    */
    bool hasValidVotingToken() const;

    /**
     * @brief Gets the user's personal data
     * 
     * @return The decrypted personal data of the user
    */
    std::string getPersonalData() const;
};

#endif