#ifndef VOTEFACTORY_H
#define VOTEFACTORY_H

#include <memory>
#include "Vote.h"
#include "VotingToken.h"

class VoteFactory
{
public:
    static std::unique_ptr<Vote> createVote(const std::string& choice);
    static std::unique_ptr<VotingToken> createVotingToken(int value);
};

#endif