cmake_minimum_required(VERSION 3.10)

set(This CryptoVote)
project(${This})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(CryptoVote 
    src/main.cpp
    src/Block.h
    src/Block.cpp
    src/Blockchain.h
    src/Blockchain.cpp
    src/User.h
    src/User.cpp
    src/Wallet.h
    src/Wallet.cpp
    src/VotingToken.h
    src/VotingToken.cpp
    src/Vote.h
    src/Vote.cpp
    src/VoteFactory.h
    src/VoteFactory.cpp
    src/SecurityManager.h
    src/SecurityManager.cpp
)

target_link_libraries(CryptoVote cryptopp)

enable_testing()
add_subdirectory(test)
add_subdirectory(src)