/**
 * @file SecurityManager.h
 * @brief Declaration of the SecurityManager class
*/

#ifndef SECURITY_MANAGER_H
#define SECURITY_MANAGER_H

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

/**
 * @class SecurityManager
 * @brief Manages encryption and decryption operations
*/
class SecurityManager
{
private:
    static std::unique_ptr<SecurityManager> instance; /**< Singleton instance of the SecurityManager */
    std::map<std::string, std::vector<unsigned char>> encryptionKeys; /**< Map of encryption keys */
    std::map<std::string, std::string> certificates; /**< Map of certificates */

    /**
     * @brief Private constructor for the SecurityManager class
    */
    SecurityManager() {}

public:
    /**
     * @brief Gets the singleton instance of the SecurityManager
     * 
     * @return Pointer to the singleton instance of the SecurityManager
    */
    static SecurityManager* getInstance()
    {
        if (instance == nullptr)
            instance = std::unique_ptr<SecurityManager>(new SecurityManager());
        return instance.get();
    }

    /**
     * @brief Encrypts the given plaintext using the specified key
     * 
     * @param plaintext The plaintext to encrypt
     * @param keyName The name of the encryption key
     * @return The encrypted ciphertext
     * @throw std::invalid_argument if the key is not found
     * @throw std::runtime_error if there is an error during encryption
    */
    std::string encrypt(const std::string& plaintext, const std::string& keyName);

    /**
     * @brief Decrypts the given ciphertext using the specified key
     * 
     * @param ciphertext The ciphertext to encrypt
     * @param keyName The name of the encryption key
     * @return The decrypted plaintext
     * @throw std::invalid_argument if the key is not found
     * @throw std::runtime_error if there is an error during decryption
    */
    std::string decrypt(const std::string& ciphertext, const std::string& keyName);

    /**
     * @brief Generate encryption keys
    */
    void generateKeys();

    /**
     * @brief Adds an encryption key
     * 
     * @param keyName The name of the key
     * @param keyValue The value of the key
     * @throw std::runtime_error if the key length is invalid
    */
    void addEncryptionKey(const std::string& keyName, const std::vector<unsigned char>& keyValue)
    {
        if (keyValue.size() != CryptoPP::AES::DEFAULT_KEYLENGTH)
        {
            std::cerr << "Invalid key length: " << keyValue.size() << std::endl;
            throw std::runtime_error("Invalid key length");
        }
        
        encryptionKeys[keyName] = keyValue;
    }

    /**
     * @brief Adds a certificate
     * 
     * @param certName The name of the certificate
     * @param certValue The value of the certifiate
    */
    void addCertificate(const std::string& certName, const std::string& certValue)
    {
        certificates[certName] = certValue;
    }

    /**
     * @brief Gets an encryption key
     * 
     * @param keyName The name of the key
     * @return The encryption key
     * @throw std::runtime_error if the key is not found
    */
    std::vector<unsigned char> getEncryptionKey(const std::string& keyName)
    {
        auto it = encryptionKeys.find(keyName);
        if (it != encryptionKeys.end())
            return it->second;
        else
            throw std::runtime_error("Encryption key not found: " + keyName);
    }

    /**
     * @brief Gets a certificate
     * 
     * @param certName The name of the certificate
     * @return The certificate
    */
    std::string getCertificate(const std::string& certName)
    {
        return certificates[certName];
    }
};

#endif