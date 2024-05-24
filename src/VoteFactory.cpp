/**
 * @file VoteFactory.cpp
 * @brief Implementation of the VoteFactory class
*/

#include "VoteFactory.h"

/**
 * @brief Creates a new Vote object
 * 
 * @param choice The choice for the vote
 * @return A unique pointer to the created Vote object
*/
std::unique_ptr<Vote> VoteFactory::createVote(const std::string& choice)
{
    return std::make_unique<Vote>(choice);
}

/**
 * @brief Creates a new VotingToken object
 * 
 * @param value The value for the voting token
 * @return A unique pointer to the created VotingToken object
*/
std::unique_ptr<VotingToken> VoteFactory::createVotingToken(int value)
{
    auto token = std::make_unique<VotingToken>();
    token->generate(value);
    return token;
}