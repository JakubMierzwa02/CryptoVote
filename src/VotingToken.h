#ifndef VOTINGTOKEN_H
#define VOTINGTOKEN_H

class VotingToken
{
private:
    int value;
    bool validity;

public:
    VotingToken();
    void generate(int val);
    void approve();
    void invalidate();
    bool isValid() const;
    int getValue() const;
};

#endif