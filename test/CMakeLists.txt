cmake_minimum_required(VERSION 3.10)

set(This CryptoVoteTest)

add_subdirectory(googletest)

add_executable(CryptoVoteTest
    security_manager_test.cpp
    ../src/SecurityManager.cpp
)

target_link_libraries(CryptoVoteTest
    gtest_main
    cryptopp
)

enable_testing()

add_test(
    NAME ${This}
    COMMAND ${This}
)