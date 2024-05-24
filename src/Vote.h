/**
 * @file Vote.h
 * @brief Declaration of the Vote class
*/

#ifndef VOTE_H
#define VOTE_H

#include <iostream>
#include <string>
#include <ctime>
#include <memory>

/**
 * @class Vote
 * @brief Represents a vote in the voting system
*/
class Vote
{
private:
    std::string choice; /**< The choice made by the vote */
    std::time_t timestamp; /**< The timestamp of when the vote was created */

public:
    /**
     * @brief Constructor for the Vote class
     * 
     * Initializes a vote with a given choice and sets the timestamp
     * 
     * @param choice The choice for the vote
    */
    Vote(const std::string& choice);

    /**
     * @brief Gets the choice of the vote
     * 
     * @return The choice of the vote
    */
    std::string getChoice() const;

    /**
     * @brief Gets the timestamp of the vote
     * 
     * @return The timestamp of the vote
    */
    std::time_t getTimestamp() const;
};

#endif