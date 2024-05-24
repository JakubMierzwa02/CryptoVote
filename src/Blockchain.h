/**
 * @file Blockchain.h
 * @brief Declaration of the Blockchain class
*/

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include <vector>

/**
 * @class Blockchain
 * @brief Represents a blockchain
*/
class Blockchain
{
private:
    /**
     * @brief Constructor for the Blockchain class
     * 
     * Initializes the blockchain with the genesis block
    */
    Blockchain();

    /**
     * @brief Creates the genesis block
     * 
     * @return The genesis block
    */
    Block createGenesisBlock() const;

public:
    std::vector<Block> listOfBlocks; /**< The list of blocks in the blockchain */

    /**
     * @brief Gets the singleton instance of the blockchain
     * 
     * @return Reference to the singleton instance of the blockchain
    */
    static Blockchain& getInstance();

    /**
     * @brief Adds a new block to the blockchain
     * 
     * @param block The block to add
     * @throw std::invalid_argument if the previous block hash does not match
    */
    void addBlock(const Block& block);

    /**
     * @brief Verifies the integrity of the blockchain
     * 
     * @return True if the blockchain is valid, false otherwise
    */
    bool verifyChain() const;
};

#endif