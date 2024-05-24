/**
 * @file Wallet.cpp
 * @brief Implementation of the Wallet class
*/

#include "Wallet.h"

/**
 * @brief Constructor for the Wallet class
 * 
 * Initializes the wallet with default values
*/
Wallet::Wallet()
    : accountBalance(0.0), votingToken(nullptr)
{

}

/**
 * @brief Generates a new wallet
 * 
 * Placeholder for wallet generation logic
*/
void Wallet::generateWallet()
{
    // Implementation of wallet generation logic
    std::cout << "Wallet generated" << std::endl;
}

/**
 * @brief Adds tokens to the wallet
 * 
 * @param amount The amount of tokens to add
*/
void Wallet::addTokens(double amount)
{
    accountBalance += amount;
    transactionHistory.push_back("Added tokens: " + std::to_string(amount));

    // Create a new block and add it to the blockchain
    Block newBlock("Add Tokens: " + std::to_string(amount), Blockchain::getInstance().listOfBlocks.back().hash);
    Blockchain::getInstance().addBlock(newBlock);
}

/**
 * @brief Spends tokens from the wallet
 * 
 * @param amount The amount of tokens to spend
*/
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

/**
 * @brief Gets the voting token from the wallet
 * 
 * @return The voting token
*/
const VotingToken& Wallet::getVotingToken() const
{
    if (votingToken)
        return *votingToken;
    else
    {
        static VotingToken invalidToken;
        invalidToken.invalidate();
        return invalidToken;
    }
}

/**
 * @brief Uses the voting token (make it invalid)
*/
void Wallet::useVotingToken()
{
    if (votingToken && votingToken->isValid())
        votingToken->invalidate();
}

/**
 * @brief Gets the account balance of the wallet
 * 
 * @return The account balance
*/
double Wallet::getBalance() const
{
    return accountBalance;
}

/**
 * @brief Gets the transaction history of the wallet
 * 
 * @return The transaction history
*/
const std::vector<std::string>& Wallet::getTransactionHistory() const
{
    return transactionHistory;
}

/**
 * @brief Adds a voting token to the wallet
 * 
 * @param token The voting token to add
*/
void Wallet::addVotingToken(std::unique_ptr<VotingToken> token)
{
    votingToken = std::move(token);
}