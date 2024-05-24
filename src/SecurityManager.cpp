/**
 * @file SecurityManager.cpp
 * @brief Implementation of the SecurityManager class
*/

#include "SecurityManager.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>

std::unique_ptr<SecurityManager> SecurityManager::instance = nullptr;

/**
 * @brief Encrypts the given plaintext using the specified key
 * 
 * @param plaintext The plaintext to encrypt
 * @param keyName The name of the encryption key
 * @return The encrypted ciphertext
 * @throw std::invalid_argument if the key is not found
 * @throw std::runtime_error if there is an error during encryption
*/
std::string SecurityManager::encrypt(const std::string& plaintext, const std::string& keyName)
{
    // Encryption logic
    if (encryptionKeys.find(keyName) == encryptionKeys.end())
        throw std::invalid_argument("Key not found");
    
    auto key = encryptionKeys[keyName];

    if (key.size() != CryptoPP::AES::DEFAULT_KEYLENGTH)
        throw std::runtime_error("Invalid key length.");

    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);

    // Generate IV
    CryptoPP::AutoSeededRandomPool prng;
    prng.GenerateBlock(iv, iv.size());

    std::string ciphertext;
    try
    {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption;
        encryption.SetKeyWithIV(key.data(), key.size(), iv);

        CryptoPP::StringSource(plaintext, true, 
            new CryptoPP::StreamTransformationFilter(encryption, 
            new CryptoPP::StringSink(ciphertext)));

    }
    catch(const std::exception& e)
    {
        throw std::runtime_error(e.what());
    }
    
    // Prepend IV to ciphertext for use in decryption
    std::string ivStr(reinterpret_cast<const char*>(iv.data()), iv.size());
    ciphertext += ivStr;

    // Encode ciphertext to Base64
    //std::string encodedCiphertext;
    //CryptoPP::StringSource(ciphertext, true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encodedCiphertext)));

    return ciphertext;
}

/**
 * @brief Decrypts the given ciphertext using the specified key
 * 
 * @param ciphertext The ciphertext to encrypt
 * @param keyName The name of the encryption key
 * @return The decrypted plaintext
 * @throw std::invalid_argument if the key is not found
 * @throw std::runtime_error if there is an error during decryption
*/
std::string SecurityManager::decrypt(const std::string& ciphertext, const std::string& keyName)
{
    // Decryption logic
    if (encryptionKeys.find(keyName) == encryptionKeys.end())
        throw std::invalid_argument("Key not found.");

    std::vector<unsigned char> key = encryptionKeys[keyName];

    if (key.size() != CryptoPP::AES::DEFAULT_KEYLENGTH)
        throw std::runtime_error("Invalid key length.");

    // Decode Base64 ciphertext to binary
    //std::string ciphertext;
    //CryptoPP::StringSource(encodedCipherText, true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(ciphertext)));

    // Extract IV
    if (ciphertext.size() < CryptoPP::AES::BLOCKSIZE)
        throw std::runtime_error("Ciphertext too short");

    std::string ivStr = ciphertext.substr(0, CryptoPP::AES::BLOCKSIZE);
    std::string enc = ciphertext.substr(CryptoPP::AES::BLOCKSIZE);

    CryptoPP::SecByteBlock iv(reinterpret_cast<const CryptoPP::byte*>(ivStr.data()), CryptoPP::AES::BLOCKSIZE);

    std::string plaintext;
    try
    {
        CryptoPP::CBC_CTS_Mode<CryptoPP::AES>::Decryption decryption;
        decryption.SetKeyWithIV(key.data(), key.size(), iv);

        CryptoPP::StringSource(enc, true, 
            new CryptoPP::StreamTransformationFilter(decryption, 
            new CryptoPP::StringSink(plaintext)));
    }
    catch(const std::exception& e)
    {
        throw std::runtime_error(e.what());
    }

    // Remove PKCS7 padding
    if (!plaintext.empty())
    {
        size_t paddingLength = static_cast<size_t>(plaintext[plaintext.size() - 1]);
        if (paddingLength > 0 && paddingLength <= CryptoPP::AES::BLOCKSIZE)
        {
            plaintext.erase(plaintext.size() - paddingLength);
        }
    }

    return plaintext;
}

/**
 * @brief Generate encryption keys
*/
void SecurityManager::generateKeys()
{
    CryptoPP::AutoSeededRandomPool prng;

    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
    prng.GenerateBlock(key, key.size());

    std::vector<unsigned char> binaryKey(key.begin(), key.end());   

    addEncryptionKey("defaultKey", binaryKey);
    addCertificate("defaultCert", "sampleCertificate");
    
    std::cout << "Keys and certs generated." << std::endl;    
}