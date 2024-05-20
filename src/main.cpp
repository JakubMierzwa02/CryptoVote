#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

#include "Block.h"
#include "Blockchain.h"

int main()
{
    try
    {
        Blockchain& blockchain = Blockchain::getInstance();

        Block block1("First Block Data", blockchain.getInstance().listOfBlocks.back().hash);
        blockchain.addBlock(block1);

        Block block2("Second Block Data", blockchain.getInstance().listOfBlocks.back().hash);
        blockchain.addBlock(block2);

        if (blockchain.verifyChain())
            std::cout << "Blockchain is valid." << std::endl;
        else
            std::cout << "Blockchain is invalid." << std::endl;

        for (const auto& block : blockchain.getInstance().listOfBlocks)
        {
            std::cout << "Block data: " << block.data << std::endl;
            std::cout << "Block hash: " << block.hash << std::endl;
            std::cout << "Previous block hash: " << block.previousBlockHash << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}