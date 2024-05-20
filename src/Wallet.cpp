#include "Wallet.h"

Wallet::Wallet()
    : accountBalance(0.0), votingToken(std::make_unique<VotingToken>())
{

}

void Wallet::generateWallet()
{
    // Implementation of wallet generation logic
    std::cout << "Wallet generated" << std::endl;
}

void Wallet::addTokens(double amount)
{
    accountBalance += amount;
    transactionHistory.push_back("Added tokens: " + std::to_string(amount));

    // Create a new block and add it to the blockchain
    Block newBlock("Add Tokens: " + std::to_string(amount), Blockchain::getInstance().listOfBlocks.back().hash);
    Blockchain::getInstance().addBlock(newBlock);
}

void Wallet::spendTokens(double amount)
{
    if (amount <= accountBalance)
    {
        accountBalance -= amount;
        transactionHistory.push_back("Spent tokens: " + std::to_string(amount));

        // Create a new block and add it to the blockchain
        Block newBlock("Spend Tokens: " + std::to_string(amount), Blockchain::getInstance().listOfBlocks.back().hash);
        Blockchain::getInstance().addBlock(newBlock);
    }
    else
    {
        std::cout << "Insufficient balance." << std::endl;
    }
}

double Wallet::getBalance() const
{
    return accountBalance;
}

const std::vector<std::string>& Wallet::getTransactionHistory() const
{
    return transactionHistory;
}