cmake_minimum_required(VERSION 3.10)

set(This CryptoVoteTest)

add_subdirectory(googletest)

add_executable(CryptoVoteTest
    test.cpp
)

target_link_libraries(CryptoVoteTest
    gtest_main
)

enable_testing()

add_test(
    NAME ${This}
    COMMAND ${This}
)