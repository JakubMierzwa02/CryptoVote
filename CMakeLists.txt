cmake_minimum_required(VERSION 3.10)

set(This CryptoVote)
project(${This})

set(CMAKE_CXX_STANDARD 17)

set(Sources
    src/main.cpp
)

set(Headers

)

add_executable(This ${Sources})

add_library(${This} STATIC ${Sources} ${Headers})

enable_testing()
add_subdirectory(test)