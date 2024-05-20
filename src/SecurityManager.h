#ifndef SECURITY_MANAGER_H
#define SECURITY_MANGER_H

#include <string>
#include <memory>
#include <map>
#include <vector>

#include <cryptopp/osrng.h>
#include <cryptopp/aes.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>

class SecurityManager
{
private:
    static std::unique_ptr<SecurityManager> instance;
    std::map<std::string, std::vector<unsigned char>> encryptionKeys;
    std::map<std::string, std::string> certificates;

    SecurityManager() {}

public:
    static SecurityManager& getInstance()
    {
        if (instance == nullptr)
            instance.reset(new SecurityManager());
        return *instance;
    }

    std::string encrypt(const std::string& plaintext, const std::string& keyName);
    std::string decrypt(const std::string& ciphertext, const std::string& keyName);
    void generateKeys();

    void addEncryptionKey(const std::string& keyName, const std::vector<unsigned char>& keyValue)
    {
        if (keyValue.size() != CryptoPP::AES::DEFAULT_KEYLENGTH)
        {
            std::cerr << "Invalid key length: " << keyValue.size() << std::endl;
            throw std::runtime_error("Invalid key length");
        }
        
        encryptionKeys[keyName] = keyValue;
    }

    void addCertificate(const std::string& certName, const std::string& certValue)
    {
        certificates[certName] = certValue;
    }

    std::vector<unsigned char> getEncryptionKey(const std::string& keyName)
    {
        auto it = encryptionKeys.find(keyName);
        if (it != encryptionKeys.end())
            return it->second;
        else
            throw std::runtime_error("Encryption key not found: " + keyName);
    }

    std::string getCertificate(const std::string& certName)
    {
        return certificates[certName];
    }
};

#endif