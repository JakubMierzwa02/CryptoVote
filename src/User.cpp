#include "User.h"

// Define static member
std::unordered_map<int, std::string> User::registeredUsers;

User::User(int id, const std::string& data)
    : userID(id), personalData(data), wallet(std::make_unique<Wallet>()), loggedIn(false)
{

}

void User::registerUser()
{
    if (registeredUsers.find(userID) == registeredUsers.end())
    {
        registeredUsers[userID] = personalData;
        std::cout << "User registered with ID: " << userID << std::endl;
    }
    else
    {
        std::cout << "User ID already registered: " << userID << std::endl;
    }
}

bool User::login()
{
    if (registeredUsers.find(userID) != registeredUsers.end())
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