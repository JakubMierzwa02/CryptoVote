#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>

class Wallet;
class VotingToken;

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

std::unordered_map<int, std::string> User::registeredUsers;

#endif