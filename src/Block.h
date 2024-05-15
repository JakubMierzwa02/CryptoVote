#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
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
    std::string hash;
    std::time_t timestamp;

    Block(const std::string& data, const std::string& previousBlockHash);
    
    std::string calculateHash() const;
};

#endif