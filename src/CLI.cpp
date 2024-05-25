/**
 * @file CLI.cpp
*/

#include "CLI.h"

/**
 * @brief Constructor for the CLI class
*/
CLI::CLI()
    : votingSystem(std::make_unique<VotingSystem>())
{
    securityManager = SecurityManager::getInstance();
    securityManager->generateKeys();
    blockchain = &Blockchain::getInstance();
}

/**
 * @brief Runs the CLI, processing user commands
*/
void CLI::run()
{
    std::string command;
    while (true)
    {
        std::cout << ">> ";
        std::cin >> command;

        if (command == "register")
            registerUser();
        else if (command == "login")
            loginUser();
        else if (command == "logout")
            logoutUser();
        else if (command == "startVoting")
            votingSystem->startVoting();
        else if (command == "endVoting")
            votingSystem->endVoting();
        else if (command == "castVote")
            castVote();
        else if (command == "countVotes")
            std::cout << votingSystem->countVotes() << std::endl;
        else if (command == "help")
            printHelp();
        else if (command == "exit")
            break;
        else
            std::cout << "Unknown command. Type 'help' for a list of commands." << std::endl;
    }
}

/**
 * @brief Prints the list of available commands
*/
void CLI::printHelp() const
{
    std::cout << " register    - Register a new user" << std::endl;
    std::cout << " login       - Login as a user" << std::endl;
    std::cout << " logout      - Logout the current user" << std::endl;
    std::cout << " startVoting - Start the voting process" << std::endl;
    std::cout << " endVoting   - End the voting process" << std::endl;
    std::cout << " castVote    - Cast a vote" << std::endl;
    std::cout << " countVotes  - Count and display the votes" << std::endl;
    std::cout << " help        - Display this help message" << std::endl;
    std::cout << " exit        - Exit the application" << std::endl;
}

/**
 * @brief Registers a new user in the voting system
*/
void CLI::registerUser()
{
    int id;
    std::string data;
    std::cout << "Enter user ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Enter personal data: ";
    std::getline(std::cin, data);

    votingSystem->registerUser(id, data);

    auto user = votingSystem->getUserByID(id);
    auto& wallet = user->getWallet();
    wallet.generateWallet();
    auto token = VoteFactory::createVotingToken(1);
    wallet.addVotingToken(std::move(token));
}

/**
 * @brief Logs in a user to the system
*/
void CLI::loginUser()
{
    int id;
    std::cout << "Enter user ID: ";
    std::cin >> id;

    auto user = votingSystem->getUserByID(id);
    if (user && user->login())
        loggedInUser = user;
    else
        std::cout << "Not registered " << std::endl;
}

/**
 * @brief Logs out the currently logged-in user
*/
void CLI::logoutUser()
{
    if (loggedInUser)
    {
        loggedInUser->logout();
        loggedInUser.reset();
    }
    else
    {
        std::cout << "No user is logged in" << std::endl;
    }
}

/**
 * @brief Casts a vote for the logged-in user
*/
void CLI::castVote()
{
    if (!loggedInUser)
    {
        std::cout << "Please log in first" << std::endl;
        return;
    }

    std::string choice;
    std::cout << "Enter your vote: ";
    std::cin.ignore();
    std::getline(std::cin, choice);

    votingSystem->castVote(loggedInUser->getUserID(), choice);
}