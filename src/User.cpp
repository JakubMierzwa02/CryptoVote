#include "User.h"

// Define static member
std::unordered_map<int, std::string> User::registeredUsers;

User::User(int id, const std::string& data)
    : userID(id), personalData(data), wallet(std::make_unique<Wallet>()), loggedIn(false)
{

}

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

bool User::isLoggedIn() const
{
    return loggedIn;
}

int User::getUserID() const
{
    return userID;
}

Wallet& User::getWallet()
{
    return *wallet;
}

bool User::hasValidVotingToken() const
{
    return wallet->getVotingToken().isValid();
}

std::string User::getPersonalData() const
{
    auto securityManager = SecurityManager::getInstance();
    return securityManager->decrypt(registeredUsers.at(userID), "defaultKey");
}