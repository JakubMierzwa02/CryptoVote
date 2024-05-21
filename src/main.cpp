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

int main()
{
    User user(1, "Personal Data");
    user.registerUser();

    if (user.login())
    {
        Wallet& wallet = user.getWallet();
        wallet.generateWallet();
        wallet.addTokens(100.0);
        wallet.spendTokens(30.0);

        std::cout << "Wallet balance: " << wallet.getBalance() << std::endl;
        for (const auto& transaction : wallet.getTransactionHistory())
        {
            std::cout << transaction << std::endl;
        }

        auto token = VoteFactory::createVotingToken(10);
        token->approve();
        std::cout << "Voting token value: " << token->getValue() << ", valid: " << token->isValid() << std::endl;

        auto vote = VoteFactory::createVote("Candidate A");
        vote->castVote();
        std::cout << "Vote choice: " << vote->getChoice() << std::endl;

        Blockchain& blockchain = Blockchain::getInstance();
        bool isChainValid = blockchain.verifyChain();
        std::cout << "Blockchain valid: " << (isChainValid ? "true" : "false") << std::endl;

        user.logout();
    }

    return 0;
}