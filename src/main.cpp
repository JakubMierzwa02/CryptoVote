#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

#include "Block.h"
#include "Blockchain.h"
#include "User.h"
#include "Vote.h"
#include "VoteFactory.h"
#include "VotingToken.h"
#include "Wallet.h"
#include "VotingSystem.h"

int main()
{
    auto securityManager = SecurityManager::getInstance();
    securityManager->generateKeys();
    
    VotingSystem votingSystem;

    votingSystem.registerUser(1, "User One");
    votingSystem.registerUser(2, "User Two");

    votingSystem.startVoting();

    for (const auto& user : votingSystem.getUsers())
    {
        auto& wallet = user->getWallet();
        wallet.generateWallet();
        auto token = VoteFactory::createVotingToken(1);
        wallet.addVotingToken(std::move(token));
    }

    votingSystem.castVote(1, "Candidate A");
    votingSystem.castVote(2, "Candidate B");

    votingSystem.castVote(1, "Candidate C");

    votingSystem.endVoting();

    votingSystem.countVotes();

    Blockchain& blockchain = Blockchain::getInstance();
    bool isChainValid = blockchain.verifyChain();
    std::cout << "Blockchain valid: " << (isChainValid ? "true" : "false") << std::endl;

    return 0;
}