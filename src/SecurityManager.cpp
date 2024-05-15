#include "SecurityManager.h"
#include <stdexcept>
#include <iostream>

std::unique_ptr<SecurityManager> SecurityManager::instance = nullptr;

std::string SecurityManager::encrypt(const std::string& plaintext, const std::string& keyName)
{
    // Encryption logic
    if (encryptionKeys.find(keyName) == encryptionKeys.end())
        throw std::invalid_argument("Key not found");
    
    std::string key = encryptionKeys[keyName];
    std::string iv(CryptoPP::AES::BLOCKSIZE, 0);

    // Generate IV
    CryptoPP::AutoSeededRandomPool prng;
    prng.GenerateBlock(reinterpret_cast<CryptoPP::byte*>(&iv[0]), iv.size());

    std::string ciphertext;
    try
    {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption;
        encryption.SetKeyWithIV(reinterpret_cast<const CryptoPP::byte*>(key.data()), key.size(), reinterpret_cast<const CryptoPP::byte*>(iv.data()));\

        CryptoPP::StringSource(plaintext, true, new CryptoPP::StreamTransformationFilter(encryption, new CryptoPP::StringSink(ciphertext)));

    }
    catch(const std::exception& e)
    {
        throw std::runtime_error(e.what());
    }
    
    // Append IV to ciphertext for use in decryption
    ciphertext = iv + ciphertext;

    // Encode ciphertext to Base64
    std::string encodedCiphertext;
    CryptoPP::StringSource(ciphertext, true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encodedCiphertext)));

    return encodedCiphertext;
}

std::string SecurityManager::decrypt(const std::string& ciphertext, const std::string& keyName)
{
    // Decryption logic
    return "";
}

void SecurityManager::generateKeys()
{
    CryptoPP::AutoSeededRandomPool prng;

    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
    prng.GenerateBlock(key, key.size());

    std::string encodedKey;
    CryptoPP::StringSource(key.data(), key.size(), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(encodedKey)));

    addEncryptionKey("defaultKey", encodedKey);
    addCertificate("defaultCert", "sampleCertificate");

    std::cout << "Keys and certs generated." << std::endl;
}