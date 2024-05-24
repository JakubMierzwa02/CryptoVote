/**
 * @file User.cpp
 * @brief Implementation of the User class
*/

#include "User.h"

// Define static member
std::unordered_map<int, std::string> User::registeredUsers;

/**
 * @brief Constructor for the User class
 * 
 * Initializes a user with a given ID and personal data
 * 
 * @param id The user ID
 * @param data The personal data of the user
*/
User::User(int id, const std::string& data)
    : userID(id), personalData(data), wallet(std::make_unique<Wallet>()), loggedIn(false)
{

}

/**
 * @brief Registers the user by encrypting their personal data
*/
void User::registerUser()
{
    auto securityManager = SecurityManager::getInstance();
    std::string encryptedData = securityManager->encrypt(personalData, "defaultKey");

    if (registeredUsers.find(userID) == registeredUsers.end())
    {
        registeredUsers[userID] = encryptedData;
        std::cout << "User registered with ID: " << userID << std::endl;
    }
    else
    {
        std::cout << "User ID already registered: " << userID << std::endl;
    }
}

/**
 * @brief Logs in the user
 * 
 * @return True if login is successful, false otherwise
*/
bool User::login()
{
    if (registeredUsers.find(userID) != registeredUsers.end() && !loggedIn)
    {
        loggedIn = true;
        std::cout << "User logged in: " << userID << std::endl;
        return true;
    }
    else
    {
        std::cout << "User ID not registered: " << userID << std::endl;
        return false;
    }
}

/**
 * @brief Logs out the user
*/
void User::logout()
{
    if (loggedIn)
    {
        loggedIn = false;
        std::cout << "User logged out: " << userID << std::endl;
    }
    else
    {
        std::cout << "User not logged in: " << userID << std::endl;
    }
}

/**
 * @brief Checks if the user is logged in
 * 
 * @return True if the user is logged in, false otherwise
*/
bool User::isLoggedIn() const
{
    return loggedIn;
}

/**
 * @brief Gets the user ID
 * 
 * @return The user ID
*/
int User::getUserID() const
{
    return userID;
}

/**
 * @brief Gets the user's wallet
 * 
 * @return Reference to the user's wallet
*/
Wallet& User::getWallet()
{
    return *wallet;
}

/**
 * @brief Checks if the user has a valid voting token
 * 
 * @return True if the user has a valid voting token, false otherwise
*/
bool User::hasValidVotingToken() const
{
    return wallet->getVotingToken().isValid();
}

/**
 * @brief Gets the user's personal data
 * 
 * @return The decrypted personal data of the user
*/
std::string User::getPersonalData() const
{
    auto securityManager = SecurityManager::getInstance();
    return securityManager->decrypt(registeredUsers.at(userID), "defaultKey");
}