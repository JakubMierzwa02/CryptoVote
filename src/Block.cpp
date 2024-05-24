/**
 * @file Block.cpp
 * @brief Implementation of the Block class
*/

#include "Block.h"

/**
 * @brief Constructor for the Block class
 * 
 * Creates a new block with given data and the hash of the previous block
 * 
 * @param data The data to store in the block
 * @param previousBlockHash The hash of the previous block
*/
Block::Block(const std::string& data, const std::string& previousBlockHash)
    : data(data), previousBlockHash(previousBlockHash), timestamp(std::time(nullptr))
{
    hash = calculateHash();
}

/**
 * @brief Calculates the hash of the block
 * 
 * Uses the SHA-256 algorithm to calculate the hash from the block's data
 * 
 * @return The hash of the block
*/
std::string Block::calculateHash() const
{
    CryptoPP::SHA256 hash;
    std::string digest;
    std::stringstream ss;

    ss << previousBlockHash << timestamp << data;

    CryptoPP::StringSource s(ss.str(), true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
    
    return digest;
}