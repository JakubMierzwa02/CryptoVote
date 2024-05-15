#include <gtest/gtest.h>
#include "../src/Block.h"
#include "../src/Blockchain.h"

// Calculating hash
TEST(BlockchainTest, CalculateHash)
{
    Block block("Test Data", "0");
    std::string expectedHash = block.calculateHash();
    EXPECT_EQ(block.hash, expectedHash);
}

// Creating Genesis Block
TEST(BlockchainTest, CreateGenesisBlock)
{
    Blockchain& blockchain = Blockchain::getInstance();
    Block genesisBlock = blockchain.listOfBlocks.front();

    EXPECT_EQ(genesisBlock.data, "Genesis Block");
    EXPECT_EQ(genesisBlock.previousBlockHash, "0");
    EXPECT_EQ(genesisBlock.hash, genesisBlock.calculateHash());
}

// Adding block to blockchain
TEST(BlockchainTest, AddBlock)
{
    Blockchain& blockchain = Blockchain::getInstance();

    Block block1("First Block Data", blockchain.listOfBlocks.back().hash);
    blockchain.addBlock(block1);
    EXPECT_EQ(blockchain.listOfBlocks.back().data, "First Block Data");

    Block block2("Second Block Data", blockchain.listOfBlocks.back().hash);
    blockchain.addBlock(block2);
    EXPECT_EQ(blockchain.listOfBlocks.back().data, "Second Block Data");
}

// Chain verification
TEST(BlockchainTest, VerifyChain)
{
    Blockchain& blockchain = Blockchain::getInstance();

    Block block1("First Block Data", blockchain.listOfBlocks.back().hash);
    blockchain.addBlock(block1);
    Block block2("Second Block Data", blockchain.listOfBlocks.back().hash);
    blockchain.addBlock(block2);

    EXPECT_TRUE(blockchain.verifyChain());
}

// Invalid chain verification
TEST(BlockchainTest, InvalidChain)
{
    Blockchain& blockchain = Blockchain::getInstance();

    Block block1("First Block Data", blockchain.listOfBlocks.back().hash);
    blockchain.addBlock(block1);
    Block block2("Second Block Data", blockchain.listOfBlocks.back().hash);
    blockchain.addBlock(block2);

    blockchain.listOfBlocks.back().data = "Tampered data";

    EXPECT_FALSE(blockchain.verifyChain());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}