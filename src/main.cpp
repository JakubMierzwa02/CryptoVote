#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

#include "Block.h"
#include "Blockchain.h"
#include "User.h"

int main()
{
    User user(1, "Personal data");
    user.registerUser();
    if (user.login())
    {
        Wallet& wallet = user.getWallet();
        wallet.generateWallet();
        wallet.addTokens(100.0);
        wallet.spendTokens(30.0);

        std::cout << "Wallet balance: " << wallet.getBalance() << std::endl;
        for (const auto& transaction : wallet.getTransactionHistory())
        {
            std::cout << transaction << std::endl;
        }

        user.logout();
    }

    return 0;
}