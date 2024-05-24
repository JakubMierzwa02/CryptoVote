/**
 * @file Blockchain.cpp
 * @brief Implementation of the Blockchain class
*/

#include "Blockchain.h"

/**
 * @brief Constructor for the Blockchain class
 * 
 * Initializes the blockchain with the genesis block
*/
Blockchain::Blockchain()
{
    listOfBlocks.push_back(createGenesisBlock());
}

/**
 * @brief Creates the genesis block
 * 
 * @return The genesis block
*/
Block Blockchain::createGenesisBlock() const
{
    return Block("Genesis Block", "0");
}

/**
 * @brief Gets the singleton instance of the blockchain
 * 
 * @return Reference to the singleton instance of the blockchain
*/
Blockchain& Blockchain::getInstance()
{
    static Blockchain instance;
    return instance;
}

/**
 * @brief Adds a new block to the blockchain
 * 
 * @param block The block to add
 * @throw std::invalid_argument if the previous block hash does not match
*/
void Blockchain::addBlock(const Block& block)
{
    if (listOfBlocks.empty())
    {
        listOfBlocks.push_back(createGenesisBlock());
    }

    const Block& previousBlock = listOfBlocks.back();

    if (block.previousBlockHash == previousBlock.hash)
    {
        listOfBlocks.push_back(block);
    }
    else
    {
        throw std::invalid_argument("The previous block hash does not match the hash of the block in the chain.");
    }
}

/**
 * @brief Verifies the integrity of the blockchain
 * 
 * @return True if the blockchain is valid, false otherwise
*/
bool Blockchain::verifyChain() const
{
    for (size_t i = 1; i < listOfBlocks.size(); ++i)
    {
        const Block& currentBlock = listOfBlocks[i];
        const Block& previousBlock = listOfBlocks[i - 1];

        if (currentBlock.hash != currentBlock.calculateHash())
        {
            return false;
        }

        if (currentBlock.previousBlockHash != previousBlock.hash)
        {
            return false;
        }
    }

    return true;
}