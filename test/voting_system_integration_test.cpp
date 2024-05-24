#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "VotingSystem.h"
#include <sstream>
#include <iostream>

class VotingSystemIntegrationTest : public ::testing::Test
{
protected:
    SecurityManager* securityManager;
    std::unique_ptr<VotingSystem> votingSystem;

    void SetUp() override
    {
        securityManager = SecurityManager::getInstance();
        securityManager->generateKeys();

        votingSystem = std::make_unique<VotingSystem>();
    }
};

TEST_F(VotingSystemIntegrationTest, UserRegistrationAndLogin)
{
    int userID = 1;
    std::string personalData = "User One";

    votingSystem->registerUser(userID, personalData);
    auto user = votingSystem->getUsers()[0];

    ASSERT_NE(user, nullptr);
    EXPECT_TRUE(user->login());
    EXPECT_TRUE(user->isLoggedIn());
}

TEST_F(VotingSystemIntegrationTest, CastAndCountVotes)
{
    int userID = 1;
    std::string personalData = "User One";
    std::string voteChoice = "Candidate A";

    votingSystem->registerUser(userID, personalData);
    votingSystem->startVoting();

    for (const auto& user : votingSystem->getUsers())
    {
        auto& wallet = user->getWallet();
        wallet.generateWallet();
        auto token = VoteFactory::createVotingToken(1);
        wallet.addVotingToken(std::move(token));
    }

    votingSystem->castVote(userID, voteChoice);
    votingSystem->endVoting();

    // Ensure vote was cast
    auto user = votingSystem->getUsers()[0];
    ASSERT_NE(user, nullptr);
    EXPECT_FALSE(user->hasValidVotingToken());

    std::string result = votingSystem->countVotes();
    EXPECT_NE(result.find("Candidate A: 1"), std::string::npos);
}

TEST_F(VotingSystemIntegrationTest, MultipleUsersVoting)
{
    int userID1 = 3;
    int userID2 = 4;
    std::string personalData1 = "User Three";
    std::string personalData2 = "User Four";
    std::string voteChoice1 = "Candidate A";
    std::string voteChoice2 = "Candidate B";

    votingSystem->registerUser(userID1, personalData1);
    votingSystem->registerUser(userID2, personalData2);
    votingSystem->startVoting();

    for (const auto& user : votingSystem->getUsers())
    {
        auto& wallet = user->getWallet();
        wallet.generateWallet();
        auto token = VoteFactory::createVotingToken(1);
        wallet.addVotingToken(std::move(token));
    }

    votingSystem->castVote(userID1, voteChoice1);
    votingSystem->castVote(userID2, voteChoice2);

    votingSystem->endVoting();

    std::string result = votingSystem->countVotes();

    EXPECT_NE(result.find("Candidate A: 1"), std::string::npos);
    EXPECT_NE(result.find("Candidate B: 1"), std::string::npos);
}

TEST_F(VotingSystemIntegrationTest, InvalidVoteWithoutToken)
{
    int userID = 5;
    std::string personalData = "User Five";
    std::string voteChoice = "Candidate A";

    votingSystem->registerUser(userID, personalData);
    auto user = votingSystem->getUsers()[0];
    ASSERT_NE(user, nullptr);

    auto& wallet = user->getWallet();
    wallet.generateWallet();
    auto token = VoteFactory::createVotingToken(1);
    wallet.addVotingToken(std::move(token));

    user->getWallet().useVotingToken();
    votingSystem->startVoting();
    votingSystem->castVote(userID, voteChoice);
    votingSystem->endVoting();

    std::string result = votingSystem->countVotes();

    EXPECT_EQ(result.find("Candidate A: 1"), std::string::npos);
}

TEST_F(VotingSystemIntegrationTest, VotingAfterEnd)
{
    int userID = 6;
    std::string personalData = "User Six";
    std::string voteChoice = "Candidate A";

    votingSystem->registerUser(userID, personalData);
    votingSystem->startVoting();
    votingSystem->endVoting();

    votingSystem->castVote(userID, voteChoice);

    std::string result = votingSystem->countVotes();

    EXPECT_EQ(result.find("Candidate A: 1"), std::string::npos);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}