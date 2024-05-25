/**
 * @file CLI.h
*/

#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <string>
#include <memory>
#include "User.h"
#include "VotingSystem.h"
#include "SecurityManager.h"
#include "Wallet.h"
#include "VoteFactory.h"
#include "Blockchain.h"

/**
 * @class CLI
 * @brief Command Line Interface for the voting system
*/
class CLI
{
private:
    std::unique_ptr<VotingSystem> votingSystem; /**< Pointer to the VotingSystem instance */
    SecurityManager* securityManager; /**< Pointer to the SecurityManager instance */
    Blockchain* blockchain; /**< Pointer to the Blockchain instance */
    std::shared_ptr<User> loggedInUser; /**< Pointer to the currently logged in user */

    /**
     * @brief Prints the list of available commands
    */
   void printHelp() const;

    /**
     * @brief Registers a new user in the voting system
    */
    void registerUser();

    /**
     * @brief Logs in a user to the system
    */
    void loginUser();

    /**
     * @brief Logs out the currently logged-in user
    */
    void logoutUser();

    /**
     * @brief Casts a vote for the logged-in user
    */
    void castVote();

public:
    /**
     * @brief Constructor for the CLI class
    */
    CLI();

    /**
     * @brief Runs the CLI, processing user commands
    */
    void run();
};

#endif