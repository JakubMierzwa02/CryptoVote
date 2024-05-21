#include <gtest/gtest.h>
#include "../src/User.h"

TEST(UserTests, RegisterUser)
{
    User user(1, "Personal Data");
    user.registerUser();
    EXPECT_TRUE(user.login());
}

TEST(UserTests, LoginLogout)
{
    User user(2, "Personal Data");
    user.registerUser();
    EXPECT_TRUE(user.login());
    user.logout();
    EXPECT_FALSE(user.isLoggedIn());
}

TEST(WalletTests, GenerateWallet)
{
    Wallet wallet;
    wallet.generateWallet();
    EXPECT_EQ(wallet.getBalance(), 0.0);
}

TEST(WalletTests, AddTokens)
{
    Wallet wallet;
    wallet.generateWallet();
    wallet.addTokens(50.0);
    EXPECT_EQ(wallet.getBalance(), 50.0);
}

TEST(WalletTests, SpendTokens)
{
    Wallet wallet;
    wallet.generateWallet();
    wallet.addTokens(100.0);
    wallet.spendTokens(40.0);
    EXPECT_EQ(wallet.getBalance(), 60.0);
}

TEST(WalletTests, InsufficientBalance)
{
    Wallet wallet;
    wallet.generateWallet();
    wallet.addTokens(30.0);
    wallet.spendTokens(50.0);
    EXPECT_EQ(wallet.getBalance(), 30.0);
}

TEST(VotingTokenTests, GenerateToken)
{
    VotingToken token;
    token.generate(10);
    EXPECT_TRUE(token.isValid());
    EXPECT_EQ(token.getValue(), 10);
}

TEST(VotingTokenTests, ApproveToken)
{
    VotingToken token;
    token.generate(5);
    token.approve();
    EXPECT_TRUE(token.isValid());
}

TEST(VotingTokenTests, InvalidateToken)
{
    VotingToken token;
    token.generate(20);
    token.invalidate();
    EXPECT_FALSE(token.isValid());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}