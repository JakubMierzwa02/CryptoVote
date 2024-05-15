#include "Blockchain.h"

Blockchain::Blockchain()
{
    listOfBlocks.push_back(createGenesisBlock());
}

Block Blockchain::createGenesisBlock() const
{
    return Block("Genesis Block", "0");
}

Blockchain& Blockchain::getInstance()
{
    static Blockchain instance;
    return instance;
}

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