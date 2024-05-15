#include "Block.h"

Block::Block(const std::string& data, const std::string& previousBlockHash)
    : data(data), previousBlockHash(previousBlockHash), timestamp(std::time(nullptr))
{
    hash = calculateHash();
    // std::cout << "Created block with data: " << data << ", previous hash: " << previousBlockHash << ", hash: " << hash << std::endl;
}

std::string Block::calculateHash() const
{
    CryptoPP::SHA256 hash;
    std::string digest;
    std::stringstream ss;

    ss << previousBlockHash << timestamp << data;

    CryptoPP::StringSource s(ss.str(), true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
    
    return digest;
}