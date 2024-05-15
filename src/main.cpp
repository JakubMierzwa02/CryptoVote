#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

#include "Block.h"
#include "SecurityManager.h"

// Forward declarations for classes
class User;
class Wallet;
class VotingToken;
class Vote;
class Blockchain;
class VotingSystem;

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

// Blockchain
class Blockchain
{
public:
    std::vector<Block> listOfBlocks;

    void addBlock(Block block);
    bool verifyChain();
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

int main()
{
    SecurityManager& securityManager = SecurityManager::getInstance();

    securityManager.generateKeys();

    std::string key = securityManager.getEncryptionKey("defaultKey");

    std::string decodedKey;
    CryptoPP::StringSource ss(key, true, new CryptoPP::HexDecoder(new CryptoPP::StringSink(decodedKey)));

    securityManager.addEncryptionKey("decodedKey", decodedKey);

    // Encrypt some data
    std::string data = "Hello world!";
    std::string encryptedData = securityManager.encrypt(data, "decodedKey");
    std::cout << "Encrypted data: " << encryptedData << std::endl;

    return 0;
}