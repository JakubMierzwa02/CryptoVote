/**
 * @file Vote.cpp
 * @brief Implementation of the Vote class
*/

#include "Vote.h"

/**
 * @brief Constructor for the Vote class
 * 
 * Initializes a vote with a given choice and sets the timestamp
 * 
 * @param choice The choice for the vote
*/
Vote::Vote(const std::string& choice)
    : choice(choice), timestamp(std::time(nullptr))
{

}

/**
 * @brief Gets the choice of the vote
 * 
 * @return The choice of the vote
*/
std::string Vote::getChoice() const
{
    return choice;
}

/**
 * @brief Gets the timestamp of the vote
 * 
 * @return The timestamp of the vote
*/
std::time_t Vote::getTimestamp() const
{
    return timestamp;
}