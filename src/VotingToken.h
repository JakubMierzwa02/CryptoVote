/**
 * @file VotingToken.h
 * @brief Declaration of the VotingToken class
*/

#ifndef VOTINGTOKEN_H
#define VOTINGTOKEN_H

/**
 * @class VotingToken
 * @brief Represents a voting token in the voting system
*/
class VotingToken
{
private:
    int value; /**< The value of the voting token */
    bool validity; /**< The validity status of the voting token */

public:
    /**
     * @brief Constructor for the VotingToken class
     * 
     * Initializes a voting token with default values
    */
    VotingToken();

    /**
     * @brief Generates a voting token with a specified value
     * 
     * @param val The value of the voting token
    */
    void generate(int val);

    /**
     * @brief Approves the voting token
    */
    void approve();

    /**
     * @brief Invalidates the voting token
    */
    void invalidate();

    /**
     * @brief Checks if the voting token is valid
     * 
     * @return True if the voting token is valid, false otherwise
    */
    bool isValid() const;

    /**
     * @brief Gets the value of the voting token
     * 
     * @return The value of the voting token
    */
    int getValue() const;
};

#endif