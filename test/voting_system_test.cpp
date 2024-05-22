#include <gtest/gtest.h>
#include "../src/VotingSystem.h"
#include "../src/VoteFactory.h"
#include "../src/Wallet.h"
#include <iostream>

TEST(VotingSystemTests, RegisterUser)
{
    VotingSystem votingSystem;
    votingSystem.registerUser(1, "User One");
    votingSystem.registerUser(2, "User Two");

    const auto& users = votingSystem.getUsers();
    ASSERT_EQ(users.size(), 2);
    EXPECT_EQ(users[0]->getUserID(), 1);
    EXPECT_EQ(users[0]->isLoggedIn(), false);
    EXPECT_EQ(users[1]->getUserID(), 2);
    EXPECT_EQ(users[1]->isLoggedIn(), false);
}

TEST(VotingSystemTests, CastVote)
{
    VotingSystem votingSystem;
    votingSystem.registerUser(1, "User One");
    votingSystem.startVoting();

    
    auto& user = votingSystem.getUsers()[0];
    auto& wallet = user->getWallet();
    auto token = VoteFactory::createVotingToken(1);
    wallet.addVotingToken(std::move(token));

    votingSystem.castVote(1, "Candidate A");

    EXPECT_FALSE(wallet.getVotingToken().isValid());
}

TEST(VotingSystemTests, CastVoteWithoutToken)
{
    VotingSystem votingSystem;
    votingSystem.registerUser(1, "User One");
    votingSystem.startVoting();

    votingSystem.castVote(1, "Candidate A");
    
    const auto& users = votingSystem.getUsers();
    EXPECT_EQ(users[0]->isLoggedIn(), true);
    EXPECT_EQ(users[0]->getWallet().getVotingToken().isValid(), false);
}

TEST(VotingSystemTests, CountVotes)
{
    VotingSystem votingSystem;
    votingSystem.registerUser(1, "User One");
    votingSystem.registerUser(2, "User Two");

    votingSystem.startVoting();

    for (auto& user : votingSystem.getUsers())
    {
        auto& wallet = user->getWallet();
        wallet.generateWallet();
        auto token = VoteFactory::createVotingToken(1);
        wallet.addVotingToken(std::move(token));
    }

    votingSystem.castVote(1, "Candidate A");
    votingSystem.castVote(2, "Candidate B");

    votingSystem.endVoting();

    testing::internal::CaptureStdout();
    votingSystem.countVotes();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Candidate A: 1"), std::string::npos);
    EXPECT_NE(output.find("Candidate B: 1"), std::string::npos);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}