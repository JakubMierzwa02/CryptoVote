/**
 * @file VoteFactory.h
 * @brief Declaration of the VoteFactory class
*/

#ifndef VOTEFACTORY_H
#define VOTEFACTORY_H

#include <memory>
#include "Vote.h"
#include "VotingToken.h"

/**
 * @class VoteFactory
 * @brief Factory class for creating Vote and VotingToken objects
*/
class VoteFactory
{
public:
    /**
     * @brief Creates a new Vote object
     * 
     * @param choice The choice for the vote
     * @return A unique pointer to the created Vote object
    */
    static std::unique_ptr<Vote> createVote(const std::string& choice);

    /**
     * @brief Creates a new VotingToken object
     * 
     * @param value The value for the voting token
     * @return A unique pointer to the created VotingToken object
    */
    static std::unique_ptr<VotingToken> createVotingToken(int value);
};

#endif