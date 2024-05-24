/**
 * @file Block.h
 * @brief Declaration of the Block class
*/

#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

/**
 * @class Block
 * @brief Represents a block in the blockchain
*/
class Block
{
public:
    std::string previousBlockHash; /**< The hash of the previous block */
    std::string data; /**< The data stored in the block */
    std::string hash; /**< The hash of the current block */
    std::time_t timestamp; /**< The timestamp of when the block was created */

    /**
     * @brief Constructor for the Block class
     * 
     * Creates a new block with given data and the hash of the previous block
     * 
     * @param data The data to store in the block
     * @param previousBlockHash The hash of the previous block
    */
    Block(const std::string& data, const std::string& previousBlockHash);
    
    /**
     * @brief Calculates the hash of the block
     * 
     * Uses the SHA-256 algorithm to calculate the hash from the block's data
     * 
     * @return The hash of the block
    */
    std::string calculateHash() const;
};

#endif