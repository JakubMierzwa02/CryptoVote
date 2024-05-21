#include "VoteFactory.h"

std::unique_ptr<Vote> VoteFactory::createVote(const std::string& choice)
{
    return std::make_unique<Vote>(choice);
}

std::unique_ptr<VotingToken> VoteFactory::createVotingToken(int value)
{
    auto token = std::make_unique<VotingToken>();
    token->generate(value);
    return token;
}