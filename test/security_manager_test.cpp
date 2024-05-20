#include <gtest/gtest.h>
#include "../src/SecurityManager.h"

class SecurityManagerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        securityManager = &SecurityManager::getInstance();
    }

    SecurityManager* securityManager;
};

TEST_F(SecurityManagerTest, GenerateAndRetrieveDefaultKey)
{
    securityManager->generateKeys();
    auto key = securityManager->getEncryptionKey("defaultKey");

    ASSERT_EQ(key.size(), CryptoPP::AES::DEFAULT_KEYLENGTH);
}

TEST_F(SecurityManagerTest, AddAndRetrieveCustomKey)
{
    std::vector<unsigned char> customKey(CryptoPP::AES::DEFAULT_KEYLENGTH, 0x01);
    securityManager->addEncryptionKey("customKey", customKey);
    auto retrievedKey = securityManager->getEncryptionKey("customKey");

    ASSERT_EQ(retrievedKey.size(), customKey.size());
    ASSERT_EQ(retrievedKey, customKey);
}

TEST_F(SecurityManagerTest, EncryptAndDecryptDefaultKey)
{
    securityManager->generateKeys();
    std::string plaintext = "Hello world!";
    std::string encryptedData = securityManager->encrypt(plaintext, "defaultKey");
    std::string decryptedData = securityManager->decrypt(encryptedData, "defaultKey");

    ASSERT_EQ(decryptedData, plaintext);
}

TEST_F(SecurityManagerTest, EncryptAndDecryptCustomKey)
{
    std::vector<unsigned char> customKey(CryptoPP::AES::DEFAULT_KEYLENGTH, 0x01);
    securityManager->addEncryptionKey("customKey", customKey);
    std::string plaintext = "Hello world!";
    std::string encryptedData = securityManager->encrypt(plaintext, "customKey");
    std::string decryptedData = securityManager->decrypt(encryptedData, "customKey");

    ASSERT_EQ(decryptedData, plaintext);
}

TEST_F(SecurityManagerTest, InvalidKeyRetrieval)
{
    ASSERT_THROW(securityManager->getEncryptionKey("nonExistentKey"), std::runtime_error);
}

TEST_F(SecurityManagerTest, InvalidKeyAddition)
{
    std::vector<unsigned char> invalidKey(CryptoPP::AES::DEFAULT_KEYLENGTH + 1, 0x01);
    ASSERT_THROW(securityManager->addEncryptionKey("invalidKey", invalidKey), std::runtime_error);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}