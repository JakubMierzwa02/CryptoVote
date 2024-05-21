#include "Vote.h"

Vote::Vote(const std::string& choice)
    : choice(choice), timestamp(std::time(nullptr))
{

}

void Vote::castVote()
{
    std::cout << "Vote cast for: " << choice << " at " << std::ctime(&timestamp);
}

std::string Vote::getChoice() const
{
    return choice;
}

std::time_t Vote::getTimestamp() const
{
    return timestamp;
}