/**
 * @file VotingToken.cpp
 * @brief Implementation of the VotingToken class
*/

#include "VotingToken.h"

/**
 * @brief Constructor for the VotingToken class
 * 
 * Initializes a voting token with default values
*/
VotingToken::VotingToken()
    : value(0), validity(true)
{

}

/**
 * @brief Generates a voting token with a specified value
 * 
 * @param val The value of the voting token
*/
void VotingToken::generate(int val)
{
    value = val;
    validity = true;
}

/**
 * @brief Approves the voting token
*/
void VotingToken::approve()
{
    validity = true;
}

/**
 * @brief Invalidates the voting token
*/
void VotingToken::invalidate()
{
    validity = false;
}

/**
 * @brief Checks if the voting token is valid
 * 
 * @return True if the voting token is valid, false otherwise
*/
bool VotingToken::isValid() const
{
    return validity;
}

/**
 * @brief Gets the value of the voting token
 * 
 * @return The value of the voting token
*/
int VotingToken::getValue() const
{
    return value;
}