#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#include "Wallet.h"

class Wallet;

class User
{
private:
    int userID;
    std::string personalData;
    std::unique_ptr<Wallet> wallet;
    static std::unordered_map<int, std::string> registeredUsers;
    bool loggedIn;

public:
    User(int id, const std::string& data);
    void registerUser();
    bool login();
    void logout();
    Wallet& getWallet();
};

#endif