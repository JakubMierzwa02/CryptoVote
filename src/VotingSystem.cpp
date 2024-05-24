/**
 * @file VotingSystem.cpp
 * @brief Implementation of the VotingSystem class
*/

#include "VotingSystem.h"

/**
 * @brief Constructor for the VotingSystem class
 * 
 * Initializes the voting system with default values
*/
VotingSystem::VotingSystem() : votingStatus(false)
{

}

/**
 * @brief Starts the voting process
*/
void VotingSystem::startVoting()
{
    if (!votingStatus)
    {
        votingStatus = true;
        std::cout << "Voting has started." << std::endl;
    }
    else
    {
        std::cout << "Voting is already in progress." << std::endl;
    }
}

/**
 * @brief Ends the voting process
*/
void VotingSystem::endVoting()
{
    if (votingStatus)
    {
        votingStatus = false;
        std::cout << "Voting has ended." << std::endl;
    }
    else
    {
        std::cout << "Voting is not in progress." << std::endl;
    }
}

/**
 * @brief Counts the votes
 * 
 * @return The result of the vote count
*/
std::string VotingSystem::countVotes()
{
    std::ostringstream result;
    if (!votingStatus)
    {
        std::unordered_map<std::string, int> voteCount;
        auto securityManager = SecurityManager::getInstance();

        for (const auto& entry : userVotes)
        {
            const std::string& encryptedChoice = entry.second;

            try
            {
                std::string decryptedChoice = securityManager->decrypt(encryptedChoice, "defaultKey");
                voteCount[decryptedChoice]++;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }

        result << "Vote count: " << std::endl;
        for (const auto& entry : voteCount)
        {
            result << entry.first << ": " << entry.second << std::endl;
        }
    }
    else
    {
        std::cout << "Voting is still in progress. Cannot count votes yet." << std::endl;
    }
    
    return result.str();
}

/**
 * @brief Gets the list of users in the voting system
 * 
 * @return The list of users
*/
const std::vector<std::shared_ptr<User>>& VotingSystem::getUsers() const
{
    return listOfUsers;
}

std::shared_ptr<User> VotingSystem::getUserByID(int userID)
{
    for (const auto& user : listOfUsers)
    {
        if (user->getUserID() == userID)
        {
            return user;
        }
    }
    return nullptr;
}

/**
 * @brief Registers a user in the voting system
 * 
 * @param userID The user ID
 * @param personalData The personal data of the user
*/
void VotingSystem::registerUser(int userID, const std::string& personalData)
{
    auto user = std::make_shared<User>(userID, personalData);
    user->registerUser();
    listOfUsers.push_back(user);
}

/**
 * @brief Casts a vote for a user
 * 
 * @param userID The user ID
 * @param choice The choice for the vote
*/
void VotingSystem::castVote(int userID, const std::string& choice)
{
    if (votingStatus)
    {
        for (const auto& user : listOfUsers)
        {
            if (userID == user->getUserID())
            {
                if (!user->isLoggedIn() && user->login())
                {
                    std::cout << "User " << userID << " logged in to cast a vote." << std::endl;
                }
                if (user->hasValidVotingToken())
                {
                    auto securityManager = SecurityManager::getInstance();
                    std::string encryptedVote = securityManager->encrypt(choice, "defaultKey");

                    auto vote = VoteFactory::createVote(encryptedVote);
                    std::cout << "User: " << userID << " cast an encrypted vote at " << vote->getTimestamp() << std::endl;

                    // Add vote to the blockchain
                    Block newBlock("Vote: " + encryptedVote, Blockchain::getInstance().listOfBlocks.back().hash);
                    Blockchain::getInstance().addBlock(newBlock);

                    userVotes[userID] = encryptedVote;

                    // Use token
                    user->getWallet().useVotingToken();
                }
                else if (!user->hasValidVotingToken())
                {
                    std::cout << "User " << userID << " does not have a valid voting token." << std::endl;
                }

                return;
            }
        }
        std::cout << "User ID " << userID << " not found or not registered." << std::endl;
    }
    else
    {
        std::cout << "Voting is not in progress. Cannot cast vote." << std::endl;
    }
}