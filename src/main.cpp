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
    SecurityManager &securityManager = SecurityManager::getInstance();

    securityManager.generateKeys();

    auto key = securityManager.getEncryptionKey("defaultKey");

    // Debug:
    std::cout << "Binary key length: " << key.size() << std::endl;

    std::cout << "Binary key: ";
    for (const auto& c : key)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    std::cout << std::endl;

    // Make sure the key length is correct
    if (key.size() != CryptoPP::AES::DEFAULT_KEYLENGTH)
    {
        std::cerr << "Error: Invalid binary key length." << std::endl;
        return 1;
    }

    securityManager.addEncryptionKey("defaultKey", key);

    // Encrypt data
    std::string data = "Hello world!";
    std::string encryptedData = securityManager.encrypt(data, "defaultKey");
    std::cout << "Encrypted Data: ";
    for (const auto& c : encryptedData)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(c));
    std::cout << std::endl;

    // Decrypt
    std::string decryptedData = securityManager.decrypt(encryptedData, "defaultKey");
    std::cout << "Decrypted Data: " << decryptedData << std::endl;

    return 0;
}