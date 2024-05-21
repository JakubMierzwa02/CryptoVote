#ifndef VOTE_H
#define VOTE_H

#include <iostream>
#include <string>
#include <ctime>
#include <memory>

class Vote
{
private:
    std::string choice;
    std::time_t timestamp;

public:
    Vote(const std::string& choice);
    void castVote();
    std::string getChoice() const;
    std::time_t getTimestamp() const;
};

#endif