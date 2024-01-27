cmake_minimum_required(VERSION 3.10)

set(This CryptoVoteTest)

add_subdirectory(googletest)

#add_executable(CryptoVoteTest

#)

#target_link_libraries(CryptoVoteTest PUBLIC
    #gtest_main
    #CryptoVote
#)

enable_testing()

add_test(
    NAME ${This}
    COMMAND ${This}
)