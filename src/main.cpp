#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

#include "Block.h"
#include "Blockchain.h"

// Forward declarations for classes
class User;
class Wallet;
class VotingToken;
class Vote;
class Blockchain;
class VotingSystem;
class SecurityManager;

// User
class User
{
public:
    std::string userID;
    std::string personalData;

    void registerUser();
    void login();
    void logout();
};

// Wallet
class Wallet
{
public:
    double accountBalance;
    std::vector<std::string> transactionHistory;

    void generateWallet();
    void addTokens(VotingToken token);
    void spendTokens(int amount);
};

// VotingToken
class VotingToken
{
public:
    int value;
    bool validity;

    void generate();
    void approve();
    void invalidate();
};

// Vote
class Vote
{
public:
    std::string choice;
    std::chrono::time_point<std::chrono::system_clock> timestamp;

    void castVote();
};

// VotingSystem
class VotingSystem
{
public:
    std::vector<User> listOfUsers;
    bool votingStatus;

    void startVoting();
    void endVoting();
    int countVotes();
};

// SecurityManager - Singleton
class SecurityManager
{
private:
    static SecurityManager* instance;
    SecurityManager() {}

public:
    std::map<std::string, std::string> encryptionKeys;
    std::vector<std::string> certificates;

    static SecurityManager* getInstance()
    {
        if (!instance)
            instance = new SecurityManager();
        return instance;
    }

    void encrypt(std::string& data);
    void decrypt(std::string& data);
    void generateKeys();
};

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