cmake_minimum_required(VERSION 3.10)

set(This CryptoVoteTest)

add_subdirectory(googletest)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(CryptoVoteTest
    # test_blockchain.cpp
    # user_test.cpp
    # vote_test.cpp
    ../src/Block.cpp
    ../src/Blockchain.cpp
    ../src/User.cpp
    ../src/Wallet.cpp
    ../src/VotingToken.cpp
    ../src/Vote.cpp
    ../src/VoteFactory.cpp
    # security_manager_test.cpp
    ../src/SecurityManager.cpp
    ../src/VotingSystem.cpp
    # voting_system_test.cpp
    voting_system_integration_test.cpp
)

target_link_libraries(CryptoVoteTest
    gtest_main
    gmock_main
    cryptopp
)

target_link_libraries(CryptoVoteTest cryptopp)

enable_testing()

add_test(
    NAME ${This}
    COMMAND ${This}
)