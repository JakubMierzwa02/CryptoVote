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
        for (const auto& entry : userVotes)
        {
            const std::string& choice = entry.second;
            voteCount[choice]++;
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
            if (!user->isLoggedIn() && user->login() && userID == user->getUserID())
            {
                auto vote = VoteFactory::createVote(choice);
                vote->castVote();
                std::cout << "User: " << userID << " cast a vote for " << choice << std::endl;

                // Add vote to the blockchain
                Block newBlock("Vote: " + choice, Blockchain::getInstance().listOfBlocks.back().hash);
                Blockchain::getInstance().addBlock(newBlock);

                userVotes[userID] = choice;  

                return;
            }
        }
    }
    else
    {
        std::cout << "Voting is not in progress. Cannot cast vote." << std::endl;
    }
}