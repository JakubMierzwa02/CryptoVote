#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include <vector>

class Blockchain
{
private:
    Blockchain();

    Block createGenesisBlock() const;

public:
    std::vector<Block> listOfBlocks;

    static Blockchain& getInstance();

    void addBlock(const Block& block);
    bool verifyChain() const;
};

#endif