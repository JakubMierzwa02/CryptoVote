cmake_minimum_required(VERSION 3.10)

set(This CryptoVoteTest)

add_subdirectory(googletest)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(CryptoVoteTest
    test_blockchain.cpp
    ../src/Block.cpp
    ../src/Blockchain.cpp
)

target_link_libraries(CryptoVoteTest
    gtest_main
)

target_link_libraries(CryptoVoteTest cryptopp)

enable_testing()

add_test(
    NAME ${This}
    COMMAND ${This}
)