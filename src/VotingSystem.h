#ifndef VOTINGSYSTEM_H
#define VOTINGSYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include "User.h"
#include "Vote.h"
#include "Blockchain.h"
#include "VoteFactory.h"

class VotingSystem
{
private:
    std::vector<std::shared_ptr<User>> listOfUsers;
    std::unordered_map<int, std::string> userVotes;
    bool votingStatus;

public:
    VotingSystem();
    void startVoting();
    void endVoting();
    void countVotes();

    void registerUser(int userID, const std::string& personalData);
    void castVote(int userID, const std::string& choice);
};

#endif