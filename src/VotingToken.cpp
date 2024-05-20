#include "VotingToken.h"

VotingToken::VotingToken()
    : value(0), validity(true)
{

}

void VotingToken::generate(int val)
{
    value = val;
    validity = true;
}

void VotingToken::approve()
{
    validity = true;
}

void VotingToken::invalidate()
{
    validity = false;
}

bool VotingToken::isValid() const
{
    return validity;
}

int VotingToken::getValue() const
{
    return value;
}