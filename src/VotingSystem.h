/**
 * @file VotingSystem.h
 * @brief Declaration of the VotingSystem class
*/

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

/**
 * @class VotingSystem
 * @brief Manages the voting process, including user registration and vote casting
*/
class VotingSystem
{
private:
    std::vector<std::shared_ptr<User>> listOfUsers; /**< List of users in the voting system */
    std::unordered_map<int, std::string> userVotes; /**< Map of user votes */
    bool votingStatus; /**< Status of the voting process */

public:
    /**
     * @brief Constructor for the VotingSystem class
     * 
     * Initializes the voting system with default values
    */
    VotingSystem();

    /**
     * @brief Starts the voting process
    */
    void startVoting();

    /**
     * @brief Ends the voting process
    */
    void endVoting();

    /**
     * @brief Counts the votes
     * 
     * @return The result of the vote count
    */
    std::string countVotes();

    /**
     * @brief Gets the list of users in the voting system
     * 
     * @return The list of users
    */
    const std::vector<std::shared_ptr<User>>& getUsers() const;

    std::shared_ptr<User> getUserByID(int userID);

    /**
     * @brief Registers a user in the voting system
     * 
     * @param userID The user ID
     * @param personalData The personal data of the user
    */
    void registerUser(int userID, const std::string& personalData);

    /**
     * @brief Casts a vote for a user
     * 
     * @param userID The user ID
     * @param choice The choice for the vote
    */
    void castVote(int userID, const std::string& choice);
};

#endif