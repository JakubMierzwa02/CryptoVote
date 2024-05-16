#include "SecurityManager.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>

std::unique_ptr<SecurityManager> SecurityManager::instance = nullptr;

std::string SecurityManager::encrypt(const std::string& plaintext, const std::string& keyName)
{
    // Encryption logic
    if (encryptionKeys.find(keyName) == encryptionKeys.end())
        throw std::invalid_argument("Key not found");
    
    std::vector<unsigned char> key = encryptionKeys[keyName];

    if (key.size() != CryptoPP::AES::DEFAULT_KEYLENGTH)
        throw std::runtime_error("Invalid key length.");

    std::string iv(CryptoPP::AES::BLOCKSIZE, 0);

    // Generate IV
    CryptoPP::AutoSeededRandomPool prng;
    prng.GenerateBlock(reinterpret_cast<CryptoPP::byte*>(&iv[0]), iv.size());

    std::string ciphertext;
    try
    {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption;
        encryption.SetKeyWithIV(reinterpret_cast<const CryptoPP::byte*>(key.data()), key.size(), reinterpret_cast<const CryptoPP::byte*>(iv.data()));

        CryptoPP::StringSource(plaintext, true, new CryptoPP::StreamTransformationFilter(encryption, new CryptoPP::StringSink(ciphertext)));

    }
    catch(const std::exception& e)
    {
        throw std::runtime_error(e.what());
    }
    
    // Append IV to ciphertext for use in decryption
    ciphertext = iv + ciphertext;

    // Encode ciphertext to Base64
    //std::string encodedCiphertext;
    //CryptoPP::StringSource(ciphertext, true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encodedCiphertext)));

    return ciphertext;
}

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

    std::string iv = ciphertext.substr(0, CryptoPP::AES::BLOCKSIZE);
    std::string enc = ciphertext.substr(CryptoPP::AES::BLOCKSIZE);

    std::string plaintext;
    try
    {
        CryptoPP::CBC_CTS_Mode<CryptoPP::AES>::Decryption decryption;
        decryption.SetKeyWithIV(reinterpret_cast<const CryptoPP::byte*>(key.data()), key.size(), reinterpret_cast<const CryptoPP::byte*>(iv.data()));

        CryptoPP::StringSource(enc, true, new CryptoPP::StreamTransformationFilter(decryption, new CryptoPP::StringSink(plaintext)));
    }
    catch(const std::exception& e)
    {
        throw std::runtime_error(e.what());
    }

    return plaintext;
}

void SecurityManager::generateKeys()
{
    CryptoPP::AutoSeededRandomPool prng;

    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
    prng.GenerateBlock(key, key.size());
    
    std::vector<unsigned char> binaryKey(key.begin(), key.end());

    // Debug:
    std::cout << "Generated Key Length: " << binaryKey.size() << std::endl;
    std::cout << "Generated Key: ";
    for (const auto &c : binaryKey)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    std::cout << std::endl;    

    addEncryptionKey("defaultKey", binaryKey);
    addCertificate("defaultCert", "sampleCertificate");
    
    std::cout << "Keys and certs generated." << std::endl;    
}