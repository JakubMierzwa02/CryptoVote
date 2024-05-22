#include "VotingSystem.h"

VotingSystem::VotingSystem() : votingStatus(false)
{

}

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

void VotingSystem::countVotes()
{
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

        std::cout << "Vote count: " << std::endl;
        for (const auto& entry : voteCount)
        {
            std::cout << entry.first << ": " << entry.second << std::endl;
        }
    }
    else
    {
        std::cout << "Voting is still in progress. Cannot count votes yet." << std::endl;
    }
}

const std::vector<std::shared_ptr<User>>& VotingSystem::getUsers() const
{
    return listOfUsers;
}

void VotingSystem::registerUser(int userID, const std::string& personalData)
{
    auto user = std::make_shared<User>(userID, personalData);
    user->registerUser();
    listOfUsers.push_back(user);
}

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
                    vote->castVote();
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