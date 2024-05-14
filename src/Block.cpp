#include "Block.h"

std::string Block::calculateHash() const
{
    CryptoPP::SHA256 hash;
    std::string digest;
    std::stringstream ss;

    ss << previousBlockHash << timestamp << data;

    CryptoPP::StringSource s(ss.str(), true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

    return digest;
}