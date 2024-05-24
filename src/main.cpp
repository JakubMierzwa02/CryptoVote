#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

#include "SecurityManager.h"
#include "VotingSystem.h"

void showMenu()
{
    std::cout << "1. Register User\n";
    std::cout << "2. Login User\n";
    std::cout << "3. Start Voting\n";
    std::cout << "4. Cast Vote\n";
    std::cout << "5. End Voting\n";
    std::cout << "6. Count Votes\n";
    std::cout << "7. Exit\n";
}

int main()
{
    auto securityManager = SecurityManager::getInstance();
    securityManager->generateKeys();

    VotingSystem votingSystem;
    int choice;
    int userID;
    std::string personalData;
    std::string voteChoice;

    while (true)
    {
        showMenu();
        std::cin >> choice;

        switch (choice)
        {
            case 1:
                std::cout << "Enter UserID: ";
                std::cin >> userID;
                std::cout << "Enter Personal Data: ";
                std::cin >> personalData;
                votingSystem.registerUser(userID, personalData);
                if (auto user = votingSystem.getUserByID(userID))
                {
                    auto& wallet = user->getWallet();
                    wallet.generateWallet();
                    auto token = VoteFactory::createVotingToken(1);
                    wallet.addVotingToken(std::move(token));
                }
                break;
            case 2:
                std::cout << "Enter UserID: ";
                std::cin >> userID;
                if (auto user = votingSystem.getUserByID(userID))
                {
                    user->login();
                }
                break;
            case 3:
                votingSystem.startVoting();
                break;
            case 4:
                std::cout << "Enter UserID: ";
                std::cin >> userID;
                std::cout << "Enter your vote: ";
                std::cin >> voteChoice;
                votingSystem.castVote(userID, voteChoice);
                break;
            case 5:
                votingSystem.endVoting();
                break;
            case 6:
                std::cout << votingSystem.countVotes() << std::endl;
                break;
            case 7:
                return 0;
            default:
                std::cout << "Invalid choice, try again\n";
        }
    }

    return 0;
}