#include <gtest/gtest.h>
#include "Vote.h"
#include "VoteFactory.h"

TEST(VoteTests, CastVote)
{
    Vote vote("Candidate A");
    vote.castVote();
    EXPECT_EQ(vote.getChoice(), "Candidate A");
}

TEST(VoteTests, Timestamp)
{
    Vote vote("Candidate B");
    std::time_t now = std::time(nullptr);
    EXPECT_EQ(vote.getTimestamp(), now);
}

TEST(VoteFactoryTests, CreateVote)
{
    auto vote = VoteFactory::createVote("Candidate C");
    EXPECT_EQ(vote->getChoice(), "Candidate C");
}

TEST(VoteFactoryTests, CreateVotingToken)
{
    auto token = VoteFactory::createVotingToken(10);
    EXPECT_EQ(token->getValue(), 10);
    EXPECT_TRUE(token->isValid());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}