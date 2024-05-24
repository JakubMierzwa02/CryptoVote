/**
 * @file Wallet.h
 * @brief Declaration of the Wallet class
*/

#ifndef WALLET_H
#define WALLET_H

#include <vector>
#include <string>
#include <memory>

#include "Block.h"
#include "Blockchain.h"
#include "VotingToken.h"

class VotingToken;

/**
 * @class Wallet
 * @brief Represents a user's wallet in the voting system
*/
class Wallet
{
private:
    double accountBalance; /**< The account balance of the wallet */
    std::vector<std::string> transactionHistory; /**< The transaction history of the wallet */
    std::unique_ptr<VotingToken> votingToken; /**< The voting token associated with the wallet */
public:
    /**
     * @brief Constructor for the Wallet class
     * 
     * Initializes the wallet with default values
    */
    Wallet();

    /**
     * @brief Generates a new wallet
     * 
     * Placeholder for wallet generation logic
    */
    void generateWallet();

    /**
     * @brief Adds tokens to the wallet
     * 
     * @param amount The amount of tokens to add
    */
    void addTokens(double amount);

    /**
     * @brief Spends tokens from the wallet
     * 
     * @param amount The amount of tokens to spend
    */
    void spendTokens(double amount);

    /**
     * @brief Gets the voting token from the wallet
     * 
     * @return The voting token
    */
    const VotingToken& getVotingToken() const;

    /**
     * @brief Uses the voting token (make it invalid)
    */
    void useVotingToken();

    /**
     * @brief Gets the account balance of the wallet
     * 
     * @return The account balance
    */
    double getBalance() const;

    /**
     * @brief Gets the transaction history of the wallet
     * 
     * @return The transaction history
    */
    const std::vector<std::string>& getTransactionHistory() const;

    /**
     * @brief Adds a voting token to the wallet
     * 
     * @param token The voting token to add
    */
    void addVotingToken(std::unique_ptr<VotingToken> token);
};

#endif