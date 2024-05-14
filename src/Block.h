#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <sstream>
#include <iomanip>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

class Block
{
public:
    std::string previousBlockHash;
    std::string data;
    std::string blockHash;
    long timestamp;

    Block(std::string data, std::string previousBlockHash) : data(data), previousBlockHash(previousBlockHash) {}
    
    std::string calculateHash() const;
};

#endif