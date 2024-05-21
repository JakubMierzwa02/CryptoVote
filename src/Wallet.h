#ifndef WALLET_H
#define WALLET_H

#include <vector>
#include <string>
#include <memory>

#include "Block.h"
#include "Blockchain.h"
#include "VotingToken.h"

class VotingToken;

class Wallet
{
private:
    double accountBalance;
    std::vector<std::string> transactionHistory;
    std::unique_ptr<VotingToken> votingToken;
public:
    Wallet();
    void generateWallet();
    void addTokens(double amount);
    void spendTokens(double amount);
    const VotingToken& getVotingToken() const;
    void useVotingToken();
    double getBalance() const;
    const std::vector<std::string>& getTransactionHistory() const;
    void addVotingToken(std::unique_ptr<VotingToken> token);
};

#endif